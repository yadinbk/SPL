//
// Created by yadinben@wincs.cs.bgu.ac.il on 10/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_MESSAGE_H
#define BOOST_ECHO_CLIENT_MESSAGE_H
#include <string>

using namespace std;

class Message{
private:
    string subscription;
    string MessageId;
    string destination;
    string frameBody;

public:
    Message();

    void setSubscription(const string &subscription);

    void setMessageId(const string &messageId);

    const string &getDestination() const;

    void setDestination(const string &destination);

    const string &getFrameBody() const;

    void setFrameBody(const string &frameBody);

};

#endif //BOOST_ECHO_CLIENT_MESSAGE_H
