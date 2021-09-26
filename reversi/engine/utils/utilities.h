#pragma once

#include <includeAll.h>

class Chip;

using namespace std;

char chipToChar(Chip* chip);


template<typename T>
T* requireNonNull(T* obj, const string& varName);


template<typename T>
bool contains(vector<T*> &v, std::function<bool(T*)> comparator);

template<typename K, typename V>
V* getOrNull(map<K, V*> &m, K &key);

int sign(int num);

template<typename T>
void clearVectorOfPointers(vector<T*>* v);

template<typename K, typename V>
void clearMapOfVectorsOfPointers(map<K, V*>* m);

