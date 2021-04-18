//
// Created by yadinben@wincs.cs.bgu.ac.il on 10/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_BOOK_H
#define BOOST_ECHO_CLIENT_BOOK_H
#include <map>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Book{
private:
    string  name;
    string genre;
    string borrowedFrom;
    bool available;

public:
    Book(string name, string genre);

    virtual ~Book();

    const string &getName();

    const string &getGenre();

    const string &getBorrowedFrom();


    bool isAvailable();

    void setBorrowedFrom( string borrowedFrom);

    void setAvailable(bool available);
};
#endif //BOOST_ECHO_CLIENT_BOOK_H
