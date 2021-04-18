//
// Created by yadinben@wincs.cs.bgu.ac.il on 10/01/2020.
//

#include "User.h"

User::User(string userName, string password) : userName(userName),
        password(password), inventory(), receiptMap(), messageMap() ,genreSubMap(), wishList() {}

User::~User() {
}

User::User(const User &other) : userName(other.userName), password(other.password), inventory(other.inventory),
receiptMap(other.receiptMap), messageMap(other.messageMap), genreSubMap(other.genreSubMap), wishList(other.wishList){
}

bool User::add(string destination, string bookName) {
    Book book(bookName, destination);
    inventory.insert({bookName, book});
    return true;
}

string User::returnBook(string genre, string bookName) {
    string borrowedFrom = inventory.find(bookName)->second.getBorrowedFrom();
    inventory.erase(bookName);
    return borrowedFrom;
}

void User::setReceiptMap(int id, string command) { //todo mutex
    receiptMap.insert({id, command});
}

map<string, Book> &User::getInventory() { //todo make sure im getting pointer to object
    return inventory;
}

const string &User::getUserName() const {
    return userName;
}

void User::wish(string bookName) {
    wishList.push_back(bookName);
}

string User::wishComesTrue(string bookName) {
    if (!wishList.empty()) {
        for (string s: wishList) {
            if (s == bookName)
                return s;
        }
    }
    return "null";
}

string User::searchBook(string bookName) { //todo ckkkkkkkkkkk
    if(!inventory.empty()) {
        auto it = inventory.begin();
        while (it != inventory.end()) {
            if (it->first == bookName) {
                return bookName;
            }
            it++;
        }
    }
    return "null";
}
string User::getFromReceiptMap(int index) {
    return receiptMap[index];
}

string User::getFromGenreSubMap(string genre) {
    return to_string(genreSubMap[genre]);
}

void User::setGenreSubMap(string genre, int id) {
    genreSubMap.insert({genre, id});
}

void User::setBorrowedFrom(string bookName, string owner) {
    inventory.find(bookName)->second.setBorrowedFrom(owner);
}

vector<string> User::getStatus(string genre) {
    vector<string> toReturn;
    if(!inventory.empty()) {
        auto it = inventory.begin();
        while (it != inventory.end()) {
            if (it->second.getGenre() == genre && it->second.isAvailable()) {
                toReturn.push_back(it->second.getName());
            }
            it++;
        }
    }
    return toReturn;
}

void User::setBookAvailability(string bookName, bool available) {
    inventory.find(bookName)->second.setAvailable(available);
}

bool User::isBookAvailable(string bookName) {
    return inventory.find(bookName)->second.isAvailable();
}


