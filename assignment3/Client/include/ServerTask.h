//
// Created by yadinben@wincs.cs.bgu.ac.il on 11/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_SERVERTASK_H
#define BOOST_ECHO_CLIENT_SERVERTASK_H

#include <iostream>
#include <mutex>
#include <thread>
#include <connectionHandler.h>
#include <User.h>

class ServerTask {
private:
    int _id;
    User *_user;
    ConnectionHandler *_connectionHandler;
    bool *_terminate;

public:
    ServerTask(int id, User &user,
            ConnectionHandler &_connectionHandler, bool &terminate);

    virtual ~ServerTask();

    ServerTask &operator=(const ServerTask &other);

    ServerTask(const ServerTask &other);
    void run();
};
#endif //BOOST_ECHO_CLIENT_SERVERTASK_H
