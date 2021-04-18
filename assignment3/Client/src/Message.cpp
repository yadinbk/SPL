//
// Created by yadinben@wincs.cs.bgu.ac.il on 10/01/2020.
//

#include "Message.h"
Message::Message() : subscription(), MessageId(), destination(), frameBody() {}

void Message::setSubscription(const string &subscription) {
    Message::subscription = subscription;
}

void Message::setMessageId(const string &messageId) {
    MessageId = messageId;
}

const string &Message::getDestination() const {
    return destination;
}

void Message::setDestination(const string &destination) {
    Message::destination = destination;
}

const string &Message::getFrameBody() const {
    return frameBody;
}

void Message::setFrameBody(const string &frameBody) {
    Message::frameBody = frameBody;
}

