#ifndef WATCHABLE_H_
#define WATCHABLE_H_

#include <string>
#include <vector>
#include "User.h"
using namespace std;

class Session;

class Watchable{
public:
    Watchable(long id, int length, const std::vector<std::string>& tags);
    virtual ~Watchable();
    virtual std::string toString() const = 0;
    virtual Watchable* getNextWatchable(Session&) const = 0;
    //self added function
    long getId() const;
    int getLength() const;
    vector<string> getTags() const;
    string tagsToString(vector<string> v) const;
    virtual string getName() const = 0;
    virtual string historyToString() const = 0;
    virtual Watchable* clone()=0;

private:
    long id;
    int length;
    std::vector<std::string> tags;
};

class Movie : public Watchable{
public:
    Movie(long id, const std::string& name, int length, const std::vector<std::string>& tags);
    virtual std::string toString() const;
    virtual Watchable* getNextWatchable(Session&) const;

    string getName() const override;
    string historyToString() const override;
    Watchable* clone() override;

private:
    std::string name;
};


class Episode: public Watchable{
public:
    Episode(long id, const std::string& seriesName,int length, int season, int episode ,const std::vector<std::string>& tags);
    std::string toString() const override;
    Watchable* getNextWatchable(Session&) const override;

    string getName() const override;
    string historyToString() const override;
    Watchable* clone() override;

private:
    std::string seriesName;
    int season;
    int episode;
    long nextEpisodeId;
};

#endif