//
// Created by yadinbk on 24/11/2019.
//
#include "Watchable.h"
#include <string>
#include <vector>
#include <iostream>
#include <User.h>
#include "Session.h"

using namespace std;

Watchable::Watchable(long id, int length, const vector<std::string>& tags) : id(id), length(length), tags (tags){
}

Watchable::~Watchable() {
}

///copy constructor

//Watchable::Watchable(const Watchable &other) : id(other.getId()),length(other.length),
//tags(other.tags){
//}
//
//Watchable &Watchable::operator=(const Watchable &other) {
//    id = other.id;
//    length = other.length;
//    tags = other.tags;
//    return *this;
//}

/// public functions

long Watchable::getId() const {
    return id;
}

int Watchable::getLength() const {
    return length;
}

vector<string> Watchable::getTags() const {
    return tags;
}

string Watchable::tagsToString(vector<string> v) const{
    string s;
    for (unsigned int i=0; i<v.size(); i++){
        s = s + v[i] + ", ";
    }
    string toReturn = "";
    toReturn.append(s, 0, s.size()-2);
    return "["+toReturn+"]";
}


/// Movie

Movie::Movie(long id, const std::string& name, int length, const std::vector<std::string>& tags) : Watchable(id, length, tags), name(name){
}

std::string Movie::toString() const {
    return this->name +" " + to_string(this->getLength()) +" minutes "+ tagsToString(this->getTags());
}

Watchable *Movie::getNextWatchable(Session & curSession) const {
    User* sessionUser = curSession.getActiveUser();
    return sessionUser->getRecommendation(curSession);

}
////copy constructor
//Movie::Movie(const Movie &other) : Watchable(other.getId(), other.getLength(), other.getTags()), name(other.name){
//}
//
//Movie &Movie::operator=(const Movie &other) {
//    name = other.name;
//    return *this;
//}

string Movie::getName() const{
    return name;
}

string Movie::historyToString() const {
    return this->name;
}

Watchable *Movie::clone() {
    return new Movie(*this);
}

/// Episode

Episode::Episode(long id, const std::string &seriesName, int length, int season, int episode,
                 const std::vector<std::string> &tags) : Watchable(id, length, tags), seriesName(seriesName), season(season), episode(episode), nextEpisodeId() {
}

std::string Episode::toString() const {
    return this->seriesName +" S" + to_string(this->season)
            +"E"+ to_string(this->episode) +" " +to_string(this->getLength()) +" minutes "+
            tagsToString(this->getTags());
}

Watchable *Episode::getNextWatchable(Session & curSession)  const {
    vector<Watchable*> history = curSession.getActiveUser()->get_history();
    const unsigned int curId = history.back()->getId() -1;
    if (curId+1 >= curSession.getContent().size())
        return curSession.getActiveUser()->getRecommendation(curSession);
    else
        if (curSession.getContent()[curId]->getName() == curSession.getContent()[curId+1]->getName())
            return curSession.getContent()[curId+1];
        else
            return curSession.getActiveUser()->getRecommendation(curSession);
}

///public

string Episode::getName() const {
    return seriesName;
}

string Episode::historyToString() const {
    return this->seriesName +" S" + to_string(this->season)
           +"E"+ to_string(this->episode);
}

Watchable *Episode::clone() {
    return new Episode(*this);
}

