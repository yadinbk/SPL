//
// Created by yadinbk on 24/11/2019.
//
#include <vector>
#include <string>
#include "Session.h"
#include <fstream>
#include "json.hpp"
#include "Watchable.h"
#include <iostream>

///CONSTRUCTORS

Session::Session(const std::string &configFilePath) : content(), actionsLog(), userMap(), activeUser(nullptr), wordsVector(){
    activeUser = new LengthRecommenderUser("default");
    addUserToMap("default", activeUser);
    std::ifstream strm(configFilePath);
    nlohmann::json j = nlohmann::json::parse(strm);
    long id_counter = 1;
    //loop over movies
    size_t it_h = 0;
    while (!j["movies"][it_h].is_null()){
        size_t it_f = 0;
        std::vector<std::string> v_tags;
        while(!j["movies"][it_h]["tags"][it_f].is_null()){
            v_tags.push_back(j["movies"][it_h]["tags"][it_f]);
            it_f++;
        }
        content.push_back(new Movie(id_counter,j["movies"][it_h]["name"],j["movies"][it_h]["length"],v_tags));
        id_counter++;
        it_h++;
    }
    //loop over tv-series
    it_h = 0;
    while (!j["tv_series"][it_h].is_null()) {
        size_t it_f = 0;
        std::vector<int> v_seasons;
        std::vector<std::string> v_tags;
        while(!j["tv_series"][it_h]["seasons"][it_f].is_null() || !j["tv_series"][it_h]["tags"][it_f].is_null()) {
            if (!j["tv_series"][it_h]["seasons"][it_f].is_null()){
                v_seasons.push_back(j["tv_series"][it_h]["seasons"][it_f]);
            }
            if (!j["tv_series"][it_h]["tags"][it_f].is_null()){
                v_tags.push_back(j["tv_series"][it_h]["tags"][it_f]);
            }
            it_f++;
        }
        std::string seriesName = j["tv_series"][it_h]["name"];
        int ep_length = j["tv_series"][it_h]["episode_length"];
        for (unsigned int i=0; i < v_seasons.size(); i++) {
            for (int k = 1; k <= v_seasons[i]; k++) {
                content.push_back(new Episode(id_counter, seriesName, ep_length,i + 1,k, v_tags));
                id_counter++;
            }
        }
        it_h++;
    }
}

Session::~Session() {
    for (Watchable *w :content) {
        delete w;
    }
    content.clear();

    for (BaseAction *b: actionsLog) {
        delete b;
    }

    actionsLog.clear();
    for (pair<string, User *> p: userMap) {
        delete p.second;
    }
    userMap.clear();
    activeUser = nullptr;
    wordsVector.clear();
}


///copy constructor

Session::Session(const Session &other):content(), actionsLog(),userMap(), activeUser(), wordsVector(){
    for(unsigned int i=0; i < other.getContent().size(); i++){
        content.push_back(other.content[i]->clone());
    }
    for(unsigned int i = 0 ; i < other.getActionLog().size() ; i++){
        actionsLog.push_back(other.getActionLog()[i]->clone());
    }
    unordered_map<string,User*> mymap=other.getUserMap();
    for(auto p:mymap){
        userMap.insert({p.first , p.second->clone()});
    }
    activeUser=userMap[other.activeUser->getName()];
}

///copy assignment

Session &Session::operator=(const Session &other) {
    if (this != &other) {
        for (Watchable *w :content) {
            delete w;
        }
        content.clear();
        for (Watchable *w :other.content) {
            content.push_back(w->clone());
        }
        for (BaseAction *b: actionsLog) {
            delete b;
        }
        actionsLog.clear();
        for (BaseAction *b: other.actionsLog) {
            actionsLog.push_back(b->clone());
        }
        for (pair<string, User *> p: userMap) {
            delete p.second;
        }
        for (pair<string, User *> p: other.userMap) {
            pair<string, User *> newP(p.first, p.second->clone());

            userMap.insert(newP);
        }
        delete activeUser;
        activeUser = other.activeUser;
    }

    return *this;
}

/// move assignment

Session& Session::operator=( Session&& other) {
    if (this != &other) {
        if (!content.empty()) {
            for (Watchable *w :content) {
                delete w;
                w = nullptr;
            }
        }

        content = other.content;

        if (!actionsLog.empty()) {
            for (BaseAction *b: actionsLog) {
                delete b;
                b = nullptr;
            }
        }
        actionsLog = other.actionsLog;

        if (!userMap.empty()) {
            for (pair<string, User *> p: userMap) {
                delete p.second;
                p.second = nullptr;
            }
        }
        userMap = other.userMap;

        delete activeUser;
        activeUser = other.activeUser;
    }

    return *this;
}

///move constructor

Session::Session(Session &&other)
        : content(move(other.content)) , actionsLog(move(other.actionsLog)) , userMap(move(other.userMap)) , activeUser(other.activeUser), wordsVector() {
}

///public function

void Session::start() {
    string input;
    cout << "SPLFLIX is now on!" << endl;
    getline(cin, input);
    wordsVector = getLineToStringVector(input);

        while (wordsVector[0] != "exit") {
            if (wordsVector[0] == "createuser") {
                CreateUser *createUser = new CreateUser();
                createUser->act(*this);
            } else if (wordsVector[0] == "changeuser") {
                ChangeActiveUser *changeActiveUser = new ChangeActiveUser();

                changeActiveUser->act(*this);
            } else if (wordsVector[0] == "deleteuser") {
                DeleteUser *deleteUser = new DeleteUser();
                deleteUser->act(*this);
            } else if (wordsVector[0] == "dupuser") {
                DuplicateUser *duplicateUser = new DuplicateUser();
                duplicateUser->act(*this);
            } else if (wordsVector[0] == "content") {
                PrintContentList *printContentList = new PrintContentList();
                printContentList->act(*this);
            } else if (wordsVector[0] == "watchhist") {
                PrintWatchHistory *printWatchHistory = new PrintWatchHistory();
                printWatchHistory->act(*this);
            } else if (wordsVector[0] == "watch") {
                Watch *watch = new Watch();
                watch->act(*this);
            } else if (wordsVector[0] == "log") {
                PrintActionsLog *printActionsLog = new PrintActionsLog();
                printActionsLog->act(*this);
            }

            getline(cin, input);
            wordsVector = getLineToStringVector(input);
        }
    Exit *exit = new Exit();
    exit->act(*this);
    }

vector<BaseAction *> Session::getActionLog() const {
    return actionsLog;
}

unordered_map<string, User *> Session::getUserMap() const {
    return userMap;
}

vector<string> Session::getLineToStringVector(string input) const {
    input = input+" ";
    vector<string> wordsVector;
    string aWord;
    for (unsigned int i = 0; i < input.length(); i++) {
        if (input.at(i) != ' ') {
            aWord = aWord+input.at(i);
        }
        if (input.at(i) == ' ') {
            wordsVector.push_back(aWord);
            aWord = "";
        }
    }
    return wordsVector;
}

std::vector<Watchable *> Session::getContent() const {
    return this->content;
}

User *Session::getActiveUser() const{
    return activeUser;
}

void Session::setActiveUser(User *curUser) {
    activeUser = curUser;
}

vector<string> Session::getInputWord() const {
    return wordsVector;

}

void Session::addUserToMap(string name, User *user) {
    pair<string, User*> p(name, user);
    userMap.insert(p);
}

void Session::setActionLog(BaseAction* baseAction) {
    actionsLog.push_back(baseAction);
}


void Session::deleteUser() {
    delete userMap.at(this->getInputWord()[1]);
    userMap.erase(this->getInputWord()[1]);
}

void Session::duplicateUser() {
    User* newUser = activeUser->clone();
    newUser->setName(wordsVector[2]);
    pair<string ,User*> p(wordsVector[2], newUser);
    userMap.insert(p);
}
