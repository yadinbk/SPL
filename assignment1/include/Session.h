#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <unordered_map>
#include <string>
#include "Action.h"
using namespace std;

class User;
class Watchable;

class Session{
public:
    Session(const std::string &configFilePath);
    virtual ~Session();
    //copy constructor
    Session (const Session& other);
    //copy assignment
    Session& operator=(const Session &other);
    //move assignment
    Session& operator=( Session&& other);
    // Move Constructor
    Session(Session &&other);

    void start();
    vector<BaseAction *> getActionLog() const;
    unordered_map<string, User *> getUserMap() const;
//    self added functions
    vector<string> getLineToStringVector(string input) const;
    vector<Watchable *> getContent() const;
    User* getActiveUser() const;
    void setActiveUser(User* curUser);
    vector<string> getInputWord() const;
    void addUserToMap(string name, User* user);
    void setActionLog (BaseAction* baseAction);
    void deleteUser();
    void duplicateUser();
private:
    std::vector<Watchable*> content;
    std::vector<BaseAction*> actionsLog;
    std::unordered_map<std::string,User*> userMap;
    User* activeUser;
    //self added
    vector<string> wordsVector;
};
#endif
