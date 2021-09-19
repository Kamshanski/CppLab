#include "utils.cpp"
using namespace std;

// https://stackoverflow.com/questions/2831841/how-to-get-the-time-in-milliseconds-in-c
string randomString(int size = 15, int seed = -1) {
    if (seed != -1) {
        srand(seed);
    }

    static string CHARS =
            string("0123456789") +
            string("ABCDEFGHIJKLMNOPQRSTUVWXYZ") +
            string("abcdefghijklmnopqrstuvwxyz") +
            string("aaaaaa") +
            string("     ") +
            string(";;;;;;;");

    ostringstream o;

    for (int i = 0; i < size; ++i) {
        o << CHARS[rand() % CHARS.size()];
    }
    return o.str();
}

wstring randomWstring(int size = 15, int seed = -1) {
    return asWstring(randomString(size, seed));
}

// return how many replacements has been done
int replaceAllInString(wstring& str, wstring& oldString, wstring& newString) {
    int counter = 0;
    unsigned long long index = 0;
    while (index < str.size()) {
        index = str.find(oldString, index);
        if (index == string::npos)
            break;
        str.replace(index, oldString.size(), newString);
        counter++;
        index++;
    }
    return counter;
}

