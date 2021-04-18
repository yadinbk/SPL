//
// Created by yadinben@wincs.cs.bgu.ac.il on 10/01/2020.
//

#include "InputToStomp.h"
#include <string>
#include <vector>
#include <map>
#include <StompFrame.h>

InputToStomp::InputToStomp() : subscriptionId(0), msgId(0), receiptId(0), userName() {

}

vector<string> InputToStomp::split(const string& str, const string& delim){
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

string InputToStomp::ToSendStomp(string input) {
    StompFrame stompFrame;
    vector<string> v = split(input, " ");

    if (v.at(0) == "login") {
        stompFrame.setStompCommand("CONNECT");
        map<string, string> h_map;
        h_map.insert({"accept-version", "1.2"});
        h_map.insert({"host", "stomp.cs.bgu.ac.il"});
        h_map.insert({"login", v.at(2)});
        h_map.insert({"passcode", v.at(3)});
        stompFrame.setHeader(h_map);
    }
    if (v.at(0) == "join") {
        stompFrame.setStompCommand("SUBSCRIBE");
        map<string, string> h_map;
        h_map.insert({"destination", v.at(1)});
        h_map.insert({"id", to_string(subscriptionId)});
        h_map.insert({"receipt", to_string(receiptId)});
        stompFrame.setHeader(h_map);
    }
    if (v.at(0) == "add" || v.at(0) == "borrow" || v.at(0) == "return" || v.at(0) == "status") {
        stompFrame.setStompCommand("SEND");
        map<string, string> h_map;
        h_map.insert({"destination", v.at(1)});
//        h_map.insert({"id", to_string(subscriptionId++)});
        stompFrame.setHeader(h_map);


        string frameBody = stompFrame.createFrameBody(userName, v);
        stompFrame.setFrameBody(frameBody);
    }
    if (v.at(0) == "logout") {
        stompFrame.setStompCommand("DISCONNECT");
        map<string, string> h_map;
        h_map.insert({"receipt", to_string(receiptId)});
        stompFrame.setHeader(h_map);
    }
    if (v.at(0) == "exit") {
        stompFrame.setStompCommand("UNSUBSCRIBE");
        map<string, string> h_map;
        string subId = v[2];
        h_map.insert({"id", subId});
//        h_map.insert({"id", subId});
        stompFrame.setHeader(h_map);
    }

    //second borrow massage
    if (v.at(0) == "has") {
        stompFrame.setStompCommand("SEND");
        map<string, string> h_map;
        h_map.insert({"destination", v.at(2)});
        stompFrame.setHeader(h_map);
        string bookName;
        for(unsigned int i=3; i<v.size(); i = i+1){
            bookName += v[i] +" ";
        }
        string frameBody = v.at(1) + " has " + bookName;
        stompFrame.setFrameBody(frameBody);
    }
    //3rd borrow massage
    if (v.at(0) == "Taking") {
        stompFrame.setStompCommand("SEND");
        map<string, string> h_map;
        h_map.insert({"destination", v.at(1)});
        stompFrame.setHeader(h_map);
        string bookName;
        for(unsigned int i=3; i<v.size(); i = i+1){
            bookName += v[i] +" ";
        }
        string frameBody = "Taking " + bookName + "from " + v.at(3);
        stompFrame.setFrameBody(frameBody);
    }
    //2nd status message
    if (v.at(0) == "bookstatus") {
        stompFrame.setStompCommand("SEND");
        map<string, string> h_map;
        h_map.insert({"destination", v.at(1)});
        stompFrame.setHeader(h_map);
        string bookName;
        for(unsigned int i=3; i<v.size(); i = i+1){
            bookName += v[i] +" ";
        }
        string frameBody = v.at(2) +":"+ bookName;
        stompFrame.setFrameBody(frameBody);
    }

        string toReturn = stompFrame.toString();
    return toReturn;
}


Message InputToStomp::toStompMsg(string answer) {
    Message message;

    vector<string> tempV = InputToStomp::split(answer, "\n");
    for(string s: tempV){
        vector<string> temp = InputToStomp::split(s, ":");
        if (temp[0] == "subscription")
            message.setSubscription(temp[1]);
        if (temp[0] == "Message-id")
            message.setMessageId(temp[1]);
        if (temp[0] == "destination")
            message.setDestination(temp[1]);
    }
    message.setFrameBody(tempV[4]);
    return message;
}

int InputToStomp::incSubId() {
    int toReturn = subscriptionId++;
    return toReturn;
}

int InputToStomp::incReceiptId() {
    int toReturn = receiptId++;
    return toReturn;
}


void InputToStomp::setUserName(const string &userName) {
    InputToStomp::userName = userName;
}


