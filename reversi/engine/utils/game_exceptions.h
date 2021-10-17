#pragma once
#include <utility>

#include "includeAll.h"
using namespace std;

struct IllegalGameStateException : public std::exception {
    bool isStarted;
    string msg;

    explicit IllegalGameStateException(bool isStarted, string msg = "") : isStarted(isStarted), msg(std::move(msg)) {}

    const char* what() const noexcept override {
        ostringstream o;
        if (!isStarted) {
            o << "Game is not started yet: " << msg;
        } else {
            o << "Game is started already: " << msg;
        }

        auto* s = new string();
        *s = o.str();
        return s->c_str() ;
    }
};

struct IllegalChipException : public std::exception {
    Chip* chip;
    string msg;

    explicit IllegalChipException(Chip* ch, string msg = "") : chip(ch), msg(std::move(msg)) {}

    const char* what() const noexcept override {
        ostringstream o;
        o << "Chip " << chip << " cannot be used here: " << msg;

        auto* s = new string();
        *s = o.str();
        return s->c_str() ;
    }
};

struct IllegalMoveException : public IllegalChipException {
    int x, y;

    IllegalMoveException(Chip* ch, int x, int y, string msg = "") : IllegalChipException(ch, std::move(msg)), x(x), y(y) {}

    const char* what() const noexcept override {
        ostringstream o;
        o << "Illegal move with "
          << '\"' << chip << '\"'
          << " on position "
          << '(' << x << ", " << y << "):"
          << msg;
        auto* s = new string();
        *s = o.str();
        return s->c_str() ;
    }
};

struct IllegalPlayerNumberException : public std::exception {
    int playerNum;
    string msg;

    explicit IllegalPlayerNumberException(int playerNum, string msg = "") : playerNum(playerNum), msg(std::move(msg)) {}

    const char* what() const noexcept override {
        ostringstream o;
        o << "Illegal player number " << playerNum
          << ". Only numbers 1 and 2 are allowed: "
          << msg;
        auto* s = new string();
        *s = o.str();
        return s->c_str() ;
    }
};



struct NullPointerException : public exception {
    string msg;

    explicit NullPointerException(string msg = "") : msg(std::move(msg)) {}

    const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_USE_NOEXCEPT override {
        return msg.c_str();
    }
};