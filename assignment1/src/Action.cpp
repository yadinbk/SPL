#include <Action.h>
#include <Session.h>
#include <Watchable.h>
#include <unordered_map>

using namespace std;

///CONSTRUCTORS

BaseAction::BaseAction():errorMsg(),status(PENDING){
}

BaseAction::~BaseAction() = default;

///public functions

ActionStatus BaseAction::getStatus() const {
    return status;
}

void BaseAction::updateError(string curErrorMsg) {
    status = ERROR;
    errorMsg = curErrorMsg;
}

string BaseAction::enumToString(ActionStatus status1) const {
    std::string str="";
    if(getStatus()== PENDING ){
        str = "PENDING";
    }
    else if (getStatus() == ERROR){
        str = "ERROR:";
    }
    else {
        str = "COMPLETED";
    }
    return str;
}

///private functions

void BaseAction::complete() {
    this->status = COMPLETED;
}

void BaseAction::error(const std::string &errorMsg) {
    status = ERROR;
    this->errorMsg = errorMsg;
}


std::string BaseAction::getErrorMsg() const {
    return errorMsg;
}


///CreateUser

void CreateUser::act(Session &sess) {
    vector<string> inputVector = sess.getInputWord();

    if (sess.getUserMap().count(inputVector[1])) {
        updateError("User Name is already taken");
        cout<<"Ertor - user Name is already taken, please choose other name"<<endl;
    } else if (inputVector[2] == "len") {
        LengthRecommenderUser *newUser = new LengthRecommenderUser(inputVector[1]);
        sess.addUserToMap(inputVector[1], newUser);
        this->complete();
    } else if (inputVector[2] == "rer") {
        RerunRecommenderUser *newUser = new RerunRecommenderUser(inputVector[1]);
        sess.addUserToMap(inputVector[1], newUser);
        this->complete();
    } else if (inputVector[2] == "gen") {
        GenreRecommenderUser *newUser = new GenreRecommenderUser(inputVector[1]);
        sess.addUserToMap(inputVector[1], newUser);
        this->complete();
    } else {
        updateError("recommendation algorithm is invalid");
        cout<<"Error - recommendation algorithm is invalid"<<endl;

    }

    sess.setActionLog(this);
}

    std::string CreateUser::toString() const {
        return "CreateUser "+ enumToString(this->getStatus()) + " " + this->getErrorMsg();
    }

BaseAction *CreateUser::clone() {
    return new CreateUser(*this);
}

///ChangeActiveUser

void ChangeActiveUser::act(Session &sess) {
    vector<string> inputVector = sess.getInputWord();
    if (sess.getUserMap().find(inputVector[1]) != sess.getUserMap().end() && sess.getActiveUser()->getName() != inputVector[1]){
        sess.setActiveUser(sess.getUserMap().find(inputVector[1])->second);
        complete();
    }
    else if (sess.getActiveUser()->getName() == inputVector[1]){
        updateError("Username is already in use");
        cout<<"Error - username is already in use"<<endl;
    }
    else {
        updateError("User not found");
        cout << "Error - user not found, try again" << endl;
    }

    sess.setActionLog(this);
}

std::string ChangeActiveUser::toString() const {

    return "ChangeActiveUser "+ enumToString(this->getStatus()) + " " + this->getErrorMsg();
}

BaseAction *ChangeActiveUser::clone() {
    return new ChangeActiveUser(*this);
}

///DeleteUser

void DeleteUser::act(Session &sess) {
    if (sess.getUserMap().count(sess.getInputWord()[1])) {
        sess.deleteUser();
        complete();
    } else {
        updateError("User not found");
        cout << "User not found, try again";
    }
    sess.setActionLog(this);
}

std::string DeleteUser::toString() const {
    return "DeleteUser "+ enumToString(this->getStatus()) + " " + this->getErrorMsg();
}

BaseAction *DeleteUser::clone() {
    return new DeleteUser(*this);
}

///DuplicateUser

void DuplicateUser::act(Session &sess) {
    vector<string> inputVector = sess.getInputWord();
    if(sess.getUserMap().count(sess.getInputWord()[1]) &&
    !sess.getUserMap().count(sess.getInputWord()[2])){//ck if newUserName not exist adn old exist already

        sess.duplicateUser();
        complete();
    }
    else if (!sess.getUserMap().count(sess.getInputWord()[1])){
        updateError("User Name not found");
        cout<<"Error - user not found, try again"<<endl;
    }
    else if (sess.getUserMap().count(sess.getInputWord()[2])){
        updateError( "User Name already exist");
        cout<<"Error - user Name already exist, try again"<<endl;

    }
    sess.setActionLog(this);
}

std::string DuplicateUser::toString() const {
    return "DuplicateUser "+ enumToString(this->getStatus()) + " " + this->getErrorMsg();
}

BaseAction *DuplicateUser::clone() {
    return new DuplicateUser(*this);
}


///PrintContentList

void PrintContentList::act(Session &sess) {
    sess.setActionLog(this);
    vector<Watchable*> content = sess.getContent();
    for (unsigned int i=0; i<content.size(); i++){
        cout <<content[i]->getId() << ". " << content[i]->toString() <<endl;
    }

}

std::string PrintContentList::toString() const {
    return "PrintContentList "+ enumToString(this->getStatus()) + " " + this->getErrorMsg();

}

BaseAction *PrintContentList::clone() {
    return new PrintContentList(*this);
}

///PrintWatchHistory

void PrintWatchHistory::act(Session &sess) {
    complete();
    sess.setActionLog(this);
    vector<Watchable*> history = sess.getActiveUser()->get_history();
    cout<<"Watch History for "<<sess.getActiveUser()->getName() << endl;
    for (unsigned int i=0; i<history.size(); i++){
        cout <<history[i]->getId() << ". " << history[i]->historyToString() <<endl;
    }
}

std::string PrintWatchHistory::toString() const {
    return "PrintWatchHistory "+ enumToString(this->getStatus()) + " " + this->getErrorMsg();
}

BaseAction *PrintWatchHistory::clone() {
    return new PrintWatchHistory(*this);
}

///Watch
void Watch::act(Session &sess) {
    vector<string> inputVector = sess.getInputWord();
    int nowWatchId;
    nowWatchId = stoi(inputVector[1]) - 1;
    vector<Watchable*> content = sess.getContent();
    cout << "Watching " << content[nowWatchId]->historyToString() << endl;
    sess.getActiveUser()->setHistory(content[nowWatchId]);
    Watchable* recommendation = content[nowWatchId]->getNextWatchable(sess);
    complete();
    cout << "We recommend to watch " << recommendation->historyToString() <<
         ", continue watching? [y/n]" << endl;
    string input;
    cin >> input;
    while (input != "n") {
        if (input == "y") {
            Watch* curWatch = new Watch;
            curWatch->complete();
            sess.setActionLog(curWatch);
            cout << "Watching " << recommendation->historyToString() << endl;
        sess.getActiveUser()->setHistory(recommendation);
            recommendation = recommendation->getNextWatchable(sess);
        cout << "We recommend to watch " << recommendation->historyToString() <<
             ", continue watching? [y/n]" << endl;
    }
        cin >> input;
    }
    complete();
    sess.setActionLog(this);
}

std::string Watch::toString() const {
    return "Watch "+ enumToString(this->getStatus()) + " " + this->getErrorMsg();
}

BaseAction *Watch::clone() {
    return new Watch(*this);
}

///PrintActionsLog

void PrintActionsLog::act(Session &sess) {
    complete();
    sess.setActionLog(this);
    for(unsigned int i=0; i<sess.getActionLog().size(); i++){
        cout<<sess.getActionLog()[i]->toString() <<endl;
    }
}

std::string PrintActionsLog::toString() const {
    return "PrintActionsLog "+ enumToString(this->getStatus()) + " " + this->getErrorMsg();
}

BaseAction *PrintActionsLog::clone() {
    return new PrintActionsLog(*this);
}

///Exit

void Exit::act(Session &sess) {
    complete();
    sess.setActionLog(this);
}

std::string Exit::toString() const {
    return "Exit "+ enumToString(this->getStatus()) + " " + this->getErrorMsg();
}

BaseAction *Exit::clone() {
    return new Exit(*this);
}

