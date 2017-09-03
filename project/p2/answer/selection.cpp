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

data_type random_selection_func(data_type arr[], const size_type n, const size_type order)
{
    if (n <= 1)return arr[0];
    size_type pivotat = rand() % n;
    swap(arr[pivotat], arr[0]);
    pivotat = partition_in_place(arr, n);
    if (pivotat == order) return arr[pivotat];
    if (pivotat > order) return random_selection(arr, pivotat, order);
    return random_selection(arr + pivotat + 1, n - 1 - pivotat, order - pivotat - 1);
}

data_type random_selection(const data_type arr[], const size_type n, const size_type order)
{
    auto temp = new data_type[n];
    mem_copy(temp, arr, n);
    auto result = random_selection_func(temp, n, order);
    delete[] temp;
    return result;
}

