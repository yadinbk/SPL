//
// Created by yadinben@wincs.cs.bgu.ac.il on 11/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_INPUTTASK_H
#define BOOST_ECHO_CLIENT_INPUTTASK_H

#include <iostream>
#include <mutex>
#include <thread>
#include <connectionHandler.h>
#include <User.h>

class InputTask {
private:
    int _id;
    string _input;
    User *_user;
    ConnectionHandler *_connectionHandler;
    bool *_terminate;

public:
    InputTask(int id, string input, User &user,
            ConnectionHandler &_connectionHandler, bool &terminate);

    virtual ~InputTask();

    InputTask(const InputTask &other);

    InputTask &operator=(const InputTask &other);

    void run();
};
#endif //BOOST_ECHO_CLIENT_INPUTTASK_H
