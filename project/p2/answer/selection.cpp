//
// Created by liu on 17-9-3.
//

#include "selection.h"
#include <iostream>

using namespace std;

void mem_copy(data_type dest[], const data_type src[], const size_type n)
{
    for (size_type i = 0; i < n; i++)
        dest[i] = src[i];
}

void selection_sort(data_type arr[], const size_type n)
{
    for (size_type i = 0; i < n - 1; i++)
    {
        auto small = arr + i;
        for (size_type j = i + 1; j < n; j++)
            if (arr[j] < *small)
                small = arr + j;
        swap(arr[i], *small);
    }
}

size_type partition_in_place(data_type arr[], const size_type n)
{
    size_type i = 1, j = n - 1;
    while (true)
    {
        while (i < n - 1 && arr[i] < arr[0])i++;
        while (j > 0 && arr[j] >= arr[0])j--;
        if (i < j)swap(arr[i], arr[j]);
        else break;
    }
    swap(arr[0], arr[j]);
    return j;
}

size_type random_choose_pivot(const data_type arr[], const size_type n)
{
    return rand() % n;
}

size_type deterministic_choose_pivot(const data_type arr[], const size_type n)
{
    auto group_num = n / 5;
    auto last_n = n % 5;
    if (last_n == 0) last_n = 5;
    else group_num++;
    auto new_arr = new data_type[group_num];
    auto temp = new data_type[5];
    for (size_type i = 0; i < group_num; i++)
    {
        size_type group_n = (i == group_num - 1 ? last_n : 5);
        mem_copy(temp, arr + 5 * i, group_n);
        selection_sort(temp, group_n);
        new_arr[i] = temp[group_n / 2];
    }
    auto pivot = deterministic_selection(new_arr, n / 5, n / 10);
    delete[] new_arr;
    delete[] temp;
    for (size_type i = 0; i < n; i++)
    {
        if (arr[i] == pivot) return i;
    }
}


data_type selection_func(data_type arr[], const size_type n, const size_type order,
                         size_type (*fn)(const data_type *, const size_type))
{
    if (n <= 1)return arr[0];
    size_type pivotat = fn(arr, n);
    swap(arr[pivotat], arr[0]);
    pivotat = partition_in_place(arr, n);
    if (pivotat == order) return arr[pivotat];
    if (pivotat > order) return random_selection(arr, pivotat, order);
    return random_selection(arr + pivotat + 1, n - 1 - pivotat, order - pivotat - 1);
}

data_type selection_init(const data_type arr[], const size_type n, const size_type order,
                         size_type (*fn)(const data_type *, const size_type))
{
    auto temp = new data_type[n];
    mem_copy(temp, arr, n);
    auto result = selection_func(temp, n, order, fn);
    delete[] temp;
    return result;
}

data_type random_selection(const data_type arr[], const size_type n, const size_type order)
{
    return selection_init(arr, n, order, random_choose_pivot);
}

data_type deterministic_selection(const data_type arr[], const size_type n, const size_type order)
{
    return selection_init(arr, n, order, deterministic_choose_pivot);
}


