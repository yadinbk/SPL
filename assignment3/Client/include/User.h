//
// Created by yadinben@wincs.cs.bgu.ac.il on 10/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_USER_H
#define BOOST_ECHO_CLIENT_USER_H
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <Book.h>

using namespace std;

class User{
private:
    string userName;
    string password;
    map<string, Book> inventory;
    map<int, string> receiptMap;
    map<int, string> messageMap;
    map<string, int> genreSubMap;
    vector<string> wishList;

public:
    User(string userName, string password);

    virtual ~User();

    User (const User &other);

    bool add(string destination, string bookName);
    string returnBook(string genre, string bookName);
    void setReceiptMap(int id,string command);
    void setGenreSubMap(string genre, int id);
    void wish(string bookName);
    string wishComesTrue(string bookName);
    string searchBook(string bookName);
    void setBorrowedFrom(string bookName, string owner);
    vector<string> getStatus(string genre);
    map<string, Book> &getInventory();
    string getFromReceiptMap(int index);
    string getFromGenreSubMap(string genre);
    void setBookAvailability(string bookName, bool available);
    bool isBookAvailable(string bookName);
    const string &getUserName() const;


};
#endif //BOOST_ECHO_CLIENT_USER_H
