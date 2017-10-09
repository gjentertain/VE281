//
// Created by liu on 17-9-3.
//

#include "selection.h"

using namespace std;

inline void selection_sort(data_type arr[], const size_type n) {
    for (size_type i = 0; i < n - 1; i++) {
        auto small = arr + i;
        for (size_type j = i + 1; j < n; j++)
            if (arr[j] < *small)
                small = arr + j;
        swap(arr[i], *small);
    }
}

inline size_type partition_in_place(data_type arr[], const size_type n) {
    size_type i = 1, j = n - 1;
    while (true) {
        while (i < n - 1 && arr[i] < arr[0])i++;
        while (j > 0 && arr[j] >= arr[0])j--;
        if (i < j) swap(arr[i], arr[j]);
        else break;
    }
    swap(arr[0], arr[j]);
    return j;
}

data_type selection_func(data_type arr[], const size_type n, const size_type order,
                         size_type (*fn)(data_type *, const size_type)) {
    if (n <= 1)return arr[0];
    size_type pivotat = fn(arr, n);
    swap(arr[pivotat], arr[0]);
    pivotat = partition_in_place(arr, n);
    if (pivotat == order) return arr[pivotat];
    if (pivotat > order) return selection_func(arr, pivotat, order, fn);
    return selection_func(arr + pivotat + 1, n - 1 - pivotat, order - pivotat - 1, fn);
}

inline size_type random_choose_pivot(data_type arr[], const size_type n) {
    return rand() % n;
}

size_type deterministic_choose_pivot(data_type arr[], const size_type n) {
    auto group_num = n / 5;
    auto last_n = n % 5;
    if (last_n == 0) last_n = 5;
    else group_num++;
    auto new_arr = (data_type *) malloc(group_num * sizeof(data_type));
    for (size_type i = 0; i < group_num; i++) {
        size_type group_n = (i == group_num - 1 ? last_n : 5);
        auto temp = arr + 5 * i;
        selection_sort(temp, group_n);
        new_arr[i] = temp[group_n / 2];
    }
    auto pivot = selection_func(new_arr, n / 5, n / 10, deterministic_choose_pivot);
    free(new_arr);
    for (int i = 2; i < 5 * (group_num - 1); i += 5) {
        if (arr[i] == pivot) return size_type(i);
    }
    return n - last_n / 2 - 1;
}

data_type random_selection(data_type arr[], const size_type n, const size_type order) {
    auto result = selection_func(arr, n, order, random_choose_pivot);
    return result;
}

data_type deterministic_selection(data_type arr[], const size_type n, const size_type order) {
    auto result = selection_func(arr, n, order, deterministic_choose_pivot);
    return result;
}


