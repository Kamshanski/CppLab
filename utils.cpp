#ifndef UTILSSSSS
#define UTILSSSSS 1

#include <iostream>
#include <string>
#include <sstream>
#include <ostream>
#include <utility>
#include "math.h"
#include "random"
#include "ctime"
#include <iomanip>
#include <locale>
#include <codecvt>
#include <string>
#include <fcntl.h>
#include <io.h>
#include <cstdio>
#include <chrono>
#include <algorithm>
#include "map"
#include <unistd.h>
#include <cctype>
#include <functional>
#include "fstream"


using namespace std;

// https://www.cplusplus.com/doc/tutorial/basic_io/
double readDouble(const string& inputMsg = "") {
    string input;
    double payload = 0;

    cout << inputMsg;
    getline(cin, input);
    stringstream(input) >> payload;

    return payload;
}

int readInt(const string& inputMsg = "") {
    string input;
    int payload = 0;

    cout << inputMsg;
    getline(cin, input);
    stringstream(input) >> payload;

    return payload;
}
// https://stackoverflow.com/questions/12723509/why-must-type-getlinecin-string-twice
wstring readWstring() {
    wstring input;
    wstring waste;
    getline(wcin, input, L'\n');
    getline(wcin, waste, L'\n');
    return input;

}

// https://stackoverflow.com/a/54512651/11103179
// https://en.cppreference.com/w/cpp/io/manip/setw
template <typename T>
string joinToString(T *array,
                    int size,
                    string separator = ", ",
                    int width = 3) {
    ostringstream o;
    if (size == 0) {
        return "";
    }

    o << setw(width) << array[0];
    for (int i = 1; i < size; i++) {
        o << separator << setw(width) << array[i];
    }
    return o.str();
}

template <typename T>
string joinToString(T **matrix,
                    int rows,
                    int cols,
                    int width = 3,
                    string itemSeparator = ", ",
                    string lineSeparator = "\n") {
    ostringstream o;
    if (rows == 0 || cols == 0) {
        return "";
    }

    o << joinToString(matrix[0], cols, itemSeparator, width);
    for (int i = 1; i < rows; i++) {
        o << lineSeparator << joinToString(matrix[i], cols, itemSeparator, width);
    }
    return o.str();
}

//https://stackoverflow.com/questions/2573834/c-convert-string-or-char-to-wstring-or-wchar-t
wstring asWstring(string s) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(s);
}
string asString(wstring s) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
    return myconv.to_bytes(s);
}

int* randomIntArray(int size) {
    int* ar = new int[size];
    for (int i = 0; i < size; ++i) {
        ar[i] = (rand() & 63) - 32;
    }
    return ar;
}
double * randomDoubleArray(int size) {
    double* ar = new double[size];
    for (int i = 0; i < size; ++i) {
        ar[i] = (rand() & 63) - 32;
    }
    return ar;
}

wstring inputWstring() {
    wstring s;
    wchar_t c;
    while ((wcin >> noskipws >> c) && c > 33) {
        s += c;
    }

    return s;
}

#endif


