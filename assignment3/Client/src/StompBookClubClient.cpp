//
// Created by yadinben@wincs.cs.bgu.ac.il on 17/01/2020.
//
#include <iostream>
#include <connectionHandler.h>
#include <string>
#include "StompFrame.h"
#include "ServerTask.h"
#include "InputTask.h"
#include "InputToStomp.h"
#include "User.h"
//InputTask;


using namespace std;

int main() {
    //cut input string
    string input;
    getline(cin, input);
    InputToStomp i;
    vector<string> tempV = i.split(input, " ");
    vector<string> v = i.split(tempV.at(1), ":"); //getting host&port from input

    //connect
    ConnectionHandler connectionHandler(v.at(0), stoi(v.at(1)));
    if (!connectionHandler.connect()) {
        std::cerr << "Could not connect to server" << endl;
        connectionHandler.close();
        ///todo tryCatch to Socket::error?
        return 1;
    }

    //creating user by login input
    User user(tempV[2], tempV[3]);
    bool *terminate = new bool(false);

    ///create thread response processing the input
    InputTask inputTask(1, input, user, connectionHandler, *terminate);
    std::thread th1(&InputTask::run, &inputTask);
    ///create thread task for the listening to the socket
    ServerTask serverTask(1, user, connectionHandler, *terminate);
    std::thread th2(&ServerTask::run, &serverTask);
    th1.join();
    th2.join();

    delete terminate;

    return 0;
}

