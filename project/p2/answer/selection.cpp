//
// Created by liu on 17-9-3.
//

#include "selection.h"

using namespace std;

inline void selection_sort(pair_type arr[], const size_type n) {
    for (size_type i = 0; i < n - 1; i++) {
        auto small = arr + i;
        for (size_type j = i + 1; j < n; j++)
            if (arr[j].first < small->first)
                small = arr + j;
        arr[i].swap(*small);
    }
}

inline size_type partition_in_place(pair_type arr[], const size_type n) {
    size_type i = 1, j = n - 1;
    while (true) {
        while (i < n - 1 && arr[i].first < arr[0].first)i++;
        while (j > 0 && arr[j].first >= arr[0].first)j--;
        if (i < j) arr[i].swap(arr[j]);
        else break;
    }
    arr[0].swap(arr[j]);
    return j;
}

pair_type selection_func(pair_type arr[], const size_type n, const size_type order,
                         size_type (*fn)(const pair_type *, const size_type)) {
    if (n <= 1)return arr[0];
    size_type pivotat = fn(arr, n);
    arr[pivotat].swap(arr[0]);
    pivotat = partition_in_place(arr, n);
    if (pivotat == order) return arr[pivotat];
    if (pivotat > order) return selection_func(arr, pivotat, order, fn);
    return selection_func(arr + pivotat + 1, n - 1 - pivotat, order - pivotat - 1, fn);
}

inline size_type random_choose_pivot(const pair_type arr[], const size_type n) {
    return rand() % n;
}

size_type deterministic_choose_pivot(const pair_type arr[], const size_type n) {
    auto group_num = n / 5;
    auto last_n = n % 5;
    if (last_n == 0) last_n = 5;
    else group_num++;
    auto new_arr = (pair_type *) malloc(group_num * sizeof(pair_type));
    static pair_type temp[5] = {};
    for (size_type i = 0; i < group_num; i++) {
        size_type group_n = (i == group_num - 1 ? last_n : 5);
        for (size_type j = 0; j < group_n; j++) {
            size_type k = 5 * i + j;
            temp[j].first = arr[k].first;
            temp[j].second = k;
        }
        selection_sort(temp, group_n);
        new_arr[i].first = temp[group_n / 2].first;
        new_arr[i].second = temp[group_n / 2].second;
    }
    auto pivot = selection_func(new_arr, n / 5, n / 10, deterministic_choose_pivot);
    free(new_arr);
    return pivot.second;
}

data_type random_selection(pair_type arr[], const size_type n, const size_type order) {
    auto result = selection_func(arr, n, order, random_choose_pivot);
    return result.first;
}

data_type deterministic_selection(pair_type arr[], const size_type n, const size_type order) {
    auto result = selection_func(arr, n, order, deterministic_choose_pivot);
    return result.first;
}


