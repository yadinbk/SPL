#ifndef USER_H_
#define USER_H_

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
class Watchable;
class Session;

class User{
public:
    explicit User(const std::string& name);
    virtual ~User();
    // Copy constructor
    User(const User &other);
    // Move Constructor
    User(User &&other);
    // copy Assignment
    User& operator=(const User &other);
    // Move Assignment
    User& operator=(User &&other);

    virtual Watchable* getRecommendation(Session& s) = 0;
    std::string getName() const;
    std::vector<Watchable*> get_history() const;
    //self added user
    void setHistory(Watchable*);
    void setName(std::string name);
    virtual User* clone()=0;
protected:
    std::vector<Watchable*> history;
private:
    std::string name;
};


class LengthRecommenderUser : public User {
public:
    explicit LengthRecommenderUser(const std::string& name);
    Watchable* getRecommendation(Session& s) override;
    User* clone() override;

private:
};

class RerunRecommenderUser : public User {
public:
    explicit RerunRecommenderUser(const std::string& name);
    Watchable* getRecommendation(Session& s) override;
    User* clone() override;
private:
    int index;
};

class GenreRecommenderUser : public User {
public:
    GenreRecommenderUser(const std::string& name);
    virtual Watchable* getRecommendation(Session& s);
    virtual User* clone();
private:
};

#endif
