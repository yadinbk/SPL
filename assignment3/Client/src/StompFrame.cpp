//
// Created by yadinben@wincs.cs.bgu.ac.il on 09/01/2020.
//

#include "StompFrame.h"
#include <vector>

StompFrame::StompFrame() : stompCommand(), header(), frameBody() {}

string StompFrame::toString(){
    string s_headers;
    for (auto & it : header)
        s_headers += it.first +":" + it.second + '\n';

    return stompCommand + '\n' + s_headers + '\n' + frameBody;
}

string StompFrame::createFrameBody(string userName, vector<string> v) {
    if (v.at(0) == "add"){
        string bookName;
        for(unsigned int i=2; i<v.size(); i = i+1){
            bookName += v[i] +" ";
        }
        return userName + " has added the book " + bookName;
    }
    if (v.at(0) == "borrow"){
        string bookName;
        for(unsigned int i=2; i<v.size(); i = i+1){
            bookName += v[i] +" ";
        }
        return userName + " wish to borrow " + bookName;
    }
    if (v.at(0) == "return"){
        string bookName;
        for(unsigned int i=2; i<v.size(); i = i+1){
            bookName += v[i] +" ";
        }
        return "Returning " + bookName + " to " + userName;
    }
    if (v.at(0) == "status"){
        return "book status";
    }
    return std::__cxx11::string();
}

void StompFrame::setStompCommand(const string &stompCommand) {
    StompFrame::stompCommand = stompCommand;
}

void StompFrame::setFrameBody(const string &frameBody) {
    StompFrame::frameBody = frameBody;
}

void StompFrame::setHeader(const map<string, string> &header) {
    StompFrame::header = header;
}




