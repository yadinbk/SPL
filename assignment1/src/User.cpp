//
// Created by yadinbk on 24/11/2019.
//

#include <User.h>
#include <Watchable.h>
#include <Session.h>
#include <algorithm>
#include <string.h>
#include <map>

using namespace std;

/// CONSTRUCTORS

User::User(const std::string &name) : history(), name(name) {}

User::~User() {
    for (Watchable *h: history) {
        delete h;
    }
    history.clear();
}

/// copy constructor

User::User(const User &other) : history(), name(other.name) {
    for(unsigned int i = 0 ; i < other.get_history().size() ; i++)
        history.push_back(other.get_history()[i]->clone());
}

/// move Constructor

User::User(User &&other) : history(move(other.history)), name(move(other.name)) {
}

/// copy Assignment

User& User::operator=(const User &other) {
    if(this != &other){
        name = nullptr;
        name.clear();
        name = other.name;

        for (Watchable* h: history) {
            delete h;
        }
        history.clear();
        for (Watchable* h: other.history) {
            history.push_back(h->clone());
        }
    }
    return  *this;
}

/// Move Assignment

User& User::operator=(User &&other) {
    if(this != &other){
        name = other.getName();
        for (Watchable* h: history) {
            delete h;
            h = nullptr;
        }
    }
    return  *this;
}

/// public functions

std::string User::getName() const {
    return name;
}

vector<Watchable *> User::get_history() const {
    return history;
}

void User::setHistory(Watchable * justWatched) {
    history.push_back(justWatched->clone());
}

void User::setName(string name) {
    this->name = name;
}


/// LEN

LengthRecommenderUser::LengthRecommenderUser(const std::string &name) : User(name) {}

Watchable *LengthRecommenderUser::getRecommendation(Session &s) {
    const vector<Watchable *> content = s.getContent();
    const vector<Watchable *> his_content = s.getActiveUser()->get_history();
    double avregeTime = 0;
    int bestTimeDiff = INT32_MAX;
    Watchable *currBest;
    bool foundInHist = false;

    for(unsigned int i = 0 ; i < his_content.size() ; i++){
        avregeTime = avregeTime + his_content[i]->getLength();
    }
    avregeTime = avregeTime/his_content.size();
    for(unsigned int i = 0 ; i < content.size() ; i++) {
        if((abs(avregeTime - content[i]->getLength()) < bestTimeDiff)) {
            for (Watchable *watched : his_content) {
                if (watched->getId() == content[i]->getId())
                    foundInHist = true;
            }
            if (!foundInHist){
                currBest = content[i];
                bestTimeDiff = abs(avregeTime - content[i]->getLength());
            }
            foundInHist = false;
        }
    }
    return currBest;
}

User *LengthRecommenderUser::clone() {
    return new LengthRecommenderUser(*this);
}

/// RER

RerunRecommenderUser::RerunRecommenderUser(const std::string &name) : User(name), index(-1) {
}

Watchable *RerunRecommenderUser::getRecommendation(Session &s) {
    const vector<Watchable *> his_content = s.getActiveUser()->get_history();
    index = index + 1;
    return his_content[(index) % his_content.size()];
}

User *RerunRecommenderUser::clone() {
    return  new RerunRecommenderUser(*this);
}


/// GEN

GenreRecommenderUser::GenreRecommenderUser(const std::string &name) : User(name) {}

int comparePair(std::pair<std::string, int> elem1 ,std::pair<std::string, int> elem2)
{
    if(elem1.second != elem2.second)
        return  elem1.second > elem2.second;
    return strcmp(elem1.first.data(),elem2.first.data()) < 0;
}

Watchable *GenreRecommenderUser::getRecommendation(Session &s) {
    const vector<Watchable *> content = s.getContent();
    const vector<Watchable *> his_content = s.getActiveUser()->get_history();
    Watchable *recommend;
    map<string, int> genreCount;

    // Build Map
    for(unsigned int i =0 ; i < his_content.size() ; i++ ){
        for(unsigned int j = 0 ; j < his_content[i]->getTags().size() ; j++){
            string currGenre = his_content[i]->getTags()[j];
            map<string, int>::const_iterator iterator = genreCount.find(currGenre);
            if (iterator == genreCount.end())
                genreCount.insert(make_pair(currGenre , 1));
            else {
                genreCount[currGenre]++;
            }
        }
    }
    vector<pair<string, int>> vec(genreCount.begin(), genreCount.end());
    std::sort(vec.begin(),vec.end(),comparePair);
    bool foundMatch = false;
    for(unsigned int i = 0 ; i < vec.size() && !foundMatch ; i++){
        string favGenre = vec.at(i).first;
        for(unsigned int j = 0 ; j < content.size() && !foundMatch; j++){
            for(unsigned int k = 0 ; k < content.at(j)->getTags().size() && !foundMatch; k++){
                for(string tag : content.at(j)->getTags() ){
                    if(tag == favGenre)
                        foundMatch = true;
                }
            }
            if(foundMatch){
                for(Watchable* watched : his_content ){
                    if(watched->getId() == content.at(j)->getId())
                        foundMatch = false;
                }
                if(foundMatch) recommend = content.at(j);

            }
        }
    }
    return recommend;
}

User *GenreRecommenderUser::clone() {
    return new GenreRecommenderUser(*this);
}
