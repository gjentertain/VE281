//
// Created by liu on 17-8-30.
//

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "../answer/sort.h"

using namespace std;

void (*const sort_fns[6])(int *, const int) = {
        bubble_sort,
        insertion_sort,
        selection_sort,
        merge_sort,
        quick_sort_extra,
        quick_sort_in_place
};

int main(int argc, char *argv[]) {
    const int SIZE = (argc > 1) ? atoi(argv[1]) : 20000;
    cout << SIZE << endl;
    srand48(time(0));

    auto arr = new int[SIZE];
    auto arr_to_sort = new int[SIZE];
    auto arr_sorted = new int[SIZE];
    for (int i = 0; i < SIZE; i++) {
        arr[i] = (int) mrand48();
    }
    memcpy(arr_sorted, arr, SIZE * sizeof(int));
    sort(arr_sorted, arr_sorted + SIZE);

    for (int i = 0; i < 6; i++) {
        memcpy(arr_to_sort, arr, SIZE * sizeof(int));
        auto clock1 = clock();
        sort_fns[i](arr_to_sort, SIZE);
        auto clock2 = clock();
        auto result = memcmp(arr_sorted, arr_to_sort, SIZE * sizeof(int));

        cout << std::left << setw(12) << (double(clock2 - clock1)) / CLOCKS_PER_SEC;
        cout << (result == 0 ? "Accepted" : "Wrong Answer") << endl;

    }


//    cout << arr[0] << "\t" << arr[SIZE - 1] << endl;


    delete[] arr;
    delete[] arr_to_sort;
//    cout << mrand48();

    return 0;
}