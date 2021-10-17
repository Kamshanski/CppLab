#ifndef REER
#define REER 4
#include "includeAll.h"

char chipToChar(Chip* chip) {
    if (chip == Chip::WHITE) return '-';
    if (chip == Chip::BLACK) return 'X';
    if (chip == Chip::NONE) return ' ';
    throw IllegalChipException(chip);
}

template<typename T>
T* requireNonNull(T* obj, const string& varName) {
    if (obj == nullptr) {
        throw NullPointerException(varName + " is NULL");
    }
    return obj;
}

template<typename T>
bool contains(vector<T*> &v, std::function<bool(T*)> comparator) {
    return std::any_of(v.begin(), v.end(), comparator);
}

template<typename K, typename V>
V* getOrNull(map<K, V *> &m, K &key) {
    try {
        return m.at(key);
    } catch (out_of_range& ex) {
        return nullptr;
    }
}

int sign(int num) {
    return (num < 0) ? -1 : (num > 0) ? 1 : 0;
}

template<typename T>
void clearVectorOfPointers(vector<T*>* v) {
    if (v != nullptr) {
        for (T *item: *v) {
            delete item;
        }
        delete v;
    }
}

template<typename K, typename V>
void clearMapOfVectorsOfPointers(map<K, V*>* m) {
    if (m != nullptr) {
        for (const auto &p: *m) {
            clearVectorOfPointers(p.second);
        }
        delete m;
    }
}
#endif