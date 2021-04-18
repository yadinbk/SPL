//
// Created by yadinben@wincs.cs.bgu.ac.il on 09/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_STOMPFRAME_H
#define BOOST_ECHO_CLIENT_STOMPFRAME_H

#include <map>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class StompFrame{
private:
    string stompCommand;
    map<string , string> header;
    string frameBody;

public:
    StompFrame();
    string createFrameBody(string userName, vector<string> v);

    string toString();

    void setStompCommand(const string &stompCommand);

    void setHeader(const map<string,string> &header);

    void setFrameBody(const string &frameBody);

};

#endif //BOOST_ECHO_CLIENT_STOMPFRAME_H
