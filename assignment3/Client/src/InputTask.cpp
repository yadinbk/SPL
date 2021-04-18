//
// Created by yadinben@wincs.cs.bgu.ac.il on 11/01/2020.
//

#include "InputTask.h"
#include <mutex>
#include <boost/algorithm/string/split.hpp>
#include <InputToStomp.h>

InputTask::InputTask (int id, string input, User &user, ConnectionHandler &connectionHandler, bool &terminate) :
        _id(id), _input(input), _user(&user), _connectionHandler(&connectionHandler), _terminate(&terminate){}

InputTask::~InputTask() {}

InputTask::InputTask(const InputTask &other) :
_id(other._id), _input(other._input), _user(other._user),
_connectionHandler(other._connectionHandler), _terminate(other._terminate) {}

void InputTask::run() {

    InputToStomp i;
    while (!*_terminate) {
        vector<string> v = i.split(this->_input, " ");
        if (v[0] == "join") {
            int receiptId = i.incReceiptId();
            int subId = i.incSubId();

            i.setUserName(_user->getUserName());
            this->_user->setReceiptMap(receiptId+1, _input);
            this->_user->setGenreSubMap(v.at(1), subId+1);
        }
        if (v.at(0) == "add" || v.at(0) == "borrow" || v.at(0) == "return" || v.at(0) == "status") {
            i.setUserName(_user->getUserName());
            if (v.at(0) == "add") {
                string bookName;
                for(unsigned int i=2; i<v.size(); i = i+1){
                    bookName += v[i] +" ";
                }
                this->_user->add(v.at(1), bookName);
                cout << _user->getUserName() + " has added the book " + bookName << endl;
            }
            if (v[0] == "return") {
                string bookName;
                for(unsigned int i=2; i<v.size(); i = i+1){
                    bookName += v[i] +" ";
                }
                i.setUserName(_user->getUserName());
                string borrowedFrom = _user->returnBook(v.at(1), bookName);
                i.setUserName(borrowedFrom);
            }
            if (v[0] == "borrow") {
                string bookName;
                for(unsigned int i=2; i<v.size(); i = i+1){
                    bookName += v[i] +" ";
                }
                _user->wish(bookName);
            }
        }
        if (v[0] == "logout") {
            int receiptId = i.incReceiptId();
            _user->setReceiptMap(receiptId+1, _input);
            *_terminate = true;

        }
        if (v[0] == "exit") {
            string subId = _user->getFromGenreSubMap(v[1]);
            _input += " "+subId;
            cout << "Exited club " + v.at(1) << endl;
        }

        //sending command stomp to server
        string stompToSend = i.ToSendStomp(_input);
        if (!_connectionHandler->sendLine(stompToSend)) {
            _connectionHandler->close();
        }

        getline(cin, _input);
    }
}

InputTask &InputTask::operator=(const InputTask &other) {
    return *this;
}


