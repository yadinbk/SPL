//
// Created by yadinben@wincs.cs.bgu.ac.il on 10/01/2020.
//

#include "Book.h"

#include <utility>

Book::Book(string name, string genre) : name(name),genre(genre), borrowedFrom(), available(true) {}

Book::~Book() {

}

const string &Book::getName() {
    return name;
}

const string &Book::getGenre() {
    return genre;
}

const string &Book::getBorrowedFrom(){
    return borrowedFrom;
}

bool Book::isAvailable() {
    return available;
}

void Book::setAvailable(bool available) {
    Book::available = available;
}

void Book::setBorrowedFrom(string borrowedFrom) {
    this->borrowedFrom = borrowedFrom;
}
