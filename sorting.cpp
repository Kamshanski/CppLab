#pragma once

#include <functional>

using namespace std;
template <typename T, typename Comparator>
void selectionSort(T *arr,
                   int size,
                   bool asc = true,
                   Comparator comparator = [](const T& a, const T& b) -> bool { return a > b; }){
    if (size < 2) {
        return;
    }

    for (int i = 0; i < size; ++i) {
        T extremum = arr[i]; // max for asc or extremum for desc
        int index = i;
        for (int j = i + 1; j < size; ++j) {
            if ((asc && comparator(extremum, arr[j])) || (!asc && !comparator(extremum, arr[j]))) {
                extremum = arr[j];
                index = j;
            }
        }
        T temp = arr[i];
        arr[i] = extremum;
        arr[index] = temp;
    }
}
