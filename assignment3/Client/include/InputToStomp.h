//
// Created by yadinben@wincs.cs.bgu.ac.il on 10/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_INPUTTOSTOMP_H
#define BOOST_ECHO_CLIENT_INPUTTOSTOMP_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <atomic>
#include <Message.h>
using namespace std;

class InputToStomp {
private:
     atomic_int subscriptionId;
     atomic_int msgId;
     atomic_int receiptId;
     string userName;

public:
    InputToStomp();
    string ToSendStomp(string input);
    Message toStompMsg(string answer);
    vector<string> split(const string& str, const string& delim);

    int incSubId();
    int incReceiptId();
    void setUserName(const string &userName);
};

#endif //BOOST_ECHO_CLIENT_INPUTTOSTOMP_H
