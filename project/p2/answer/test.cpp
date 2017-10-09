//
// Created by liu on 17-10-9.
//

#include "selection.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {

    size_t size = 100000;
    auto arr = new int[size];
    auto arr2 = new int[size];
    for (int i = 0; i < size; i++) {
        arr[i] = arr2[i] = rand();
    }
    sort(arr2, arr2 + size);
    int c1 = clock();
    for (size_t i = 0; i < 100; i++) {
        auto result = deterministic_selection(arr, size, i);
        if (result != arr2[i]) cout << "error" << endl;
    }
    cout << clock() - c1 << endl;
}

