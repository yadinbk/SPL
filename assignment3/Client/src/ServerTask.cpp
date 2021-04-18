//
// Created by yadinben@wincs.cs.bgu.ac.il on 11/01/2020.
//

#include "ServerTask.h"
#include <InputToStomp.h>

ServerTask::ServerTask(int id, User &user, ConnectionHandler &connectionHandler, bool &terminate) :
_id(id), _user(&user), _connectionHandler(&connectionHandler), _terminate(&terminate){}

ServerTask::~ServerTask() {
}


ServerTask::ServerTask(const ServerTask &other) : _id(other._id), _user(other._user),
_connectionHandler(other._connectionHandler), _terminate(other._terminate){}

void ServerTask::run() {
    while (!*_terminate) {

        string answer;
        if (!_connectionHandler->getLine(answer)) {
            _connectionHandler->close();
        }

        cout << answer + '\n'+"^@" << endl; //todo test - added for the comfort of the tester

        InputToStomp i;
        vector<string> answerV = i.split(answer, "\n");

        if (answerV.at(0) == "CONNECTED") {
            cout << "Login successful" << endl;
        }
        if (answerV.at(0) == "ERROR") {
            cout << answerV[2] << endl;
            _connectionHandler->close();
        }
        if (answerV.at(0) == "RECEIPT") {
            //getting receipt id from the interior
            vector<string> receiptIdV = i.split(answerV[1], ":");
            //getting original input by receipt id
            vector<string> v = i.split(_user->getFromReceiptMap(std::stoi(receiptIdV[1]))," ");
            if (v.at(0).compare("join") == 0) {
                cout << "Joined club " + v.at(1) << endl;
            }
            if (_user->getFromReceiptMap(std::stoi(receiptIdV[1])) == "logout") {
                _connectionHandler->close();
                *_terminate = true;
            }
        }
        if (answerV.at(0) == "MESSAGE") {
            Message message = i.toStompMsg(answer);
            vector<string> v = i.split(message.getFrameBody(), " ");

            ///BORROW
            string toSend;
            if (v.size() > 1) {
                if (v.at(1) == "wish") {
                    string bookName;
                    for(unsigned int i=4; i<v.size(); i = i+1){
                        bookName += v[i] +" ";
                    }
                    if (_user->searchBook(bookName) != "null" && _user->isBookAvailable(bookName)) {
                        _user->setBookAvailability(bookName,false);
                        string toSendStomp =
                                "has " + _user->getUserName() + " " + message.getDestination() + " " + bookName;
                        toSend = i.ToSendStomp(toSendStomp);

                        if (!_connectionHandler->sendLine(toSend)) {
                            _connectionHandler->close();
                        }
                    }
                }
                if (v.at(1) == "has" && v.at(2) != "added") {
                    string bookName;
                    for(unsigned int i=2; i<v.size(); i = i+1){
                        bookName += v[i] +" ";
                    }
                    if (_user->wishComesTrue(bookName) != "null"){
                        string toSendStomp = "Taking " + message.getDestination() +" "+ v.at(0) + " " + bookName;
                        toSend = i.ToSendStomp(toSendStomp);
                        _user->add(message.getDestination(), bookName);
                        _user->setBorrowedFrom(bookName, v.at(0));
                        if (!_connectionHandler->sendLine(toSend)) {
                            _connectionHandler->close();
                        }
                    }
                }

                if (v.at(0) == "Returning") {
                    string bookName;
                    for(unsigned int i=1; i<v.size() && v[i]!="to"; i = i+1){
                        bookName += v[i] +" ";
                    }
                    if (_user->getUserName() == v.at(v.size()-1)) {
                        _user->setBookAvailability(bookName, true);
                    }
                }

                if (v.at(1) == "status") {
                    vector<string> statusV = _user->getStatus(message.getDestination());
                    string books;
                    for (string s: statusV) {
                        books += s + ",";
                    }
                    books = books.substr(0, books.size() - 1);
                    cout << _user->getUserName() + ":" + books<<endl; //todo its not in assignment instruction but we told we should print it
                    string toSendStomp =
                            "bookstatus " + message.getDestination() + " " + _user->getUserName() + " " + books;
                    toSend = i.ToSendStomp(toSendStomp);
                    if (!_connectionHandler->sendLine(toSend)) {
                        _connectionHandler->close();
                    }
                }
            }
        }
    }
}

ServerTask &ServerTask::operator=(const ServerTask &other) {
    return *this;
}
