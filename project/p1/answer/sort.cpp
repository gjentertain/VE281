//
// Created by liu on 17-8-30.
//

#include <cstdlib>
#include <iostream>
#include "sort.h"

using namespace std;


void mem_copy(int dest[], const int src[], const int n)
{
    for (int i = 0; i < n; i++)
        dest[i] = src[i];
}

void bubble_sort(int arr[], const int n)
{
    for (int i = n - 2; i >= 0; i--)
        for (int j = 0; j <= i; j++)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}

void insertion_sort(int arr[], const int n)
{
    for (int i = 1; i < n; i++)
    {
        auto temp = arr[i];
        auto j = i;
        while (j >= 1)
        {
            if (arr[j - 1] > temp)
            {
                arr[j] = arr[j - 1];
                j--;
            } else break;
        }
        arr[j] = temp;
    }
}

void selection_sort(int arr[], const int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        auto small = arr + i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < *small)
                small = arr + j;
        swap(arr[i], *small);
    }
}

void merge(int arr[], const int n, const int offset)
{
    auto temp = new int[n];
    mem_copy(temp, arr, n);
    int i = 0, j = offset, k = 0;
    while (i < offset && j < n)
        arr[k++] = temp[i] <= temp[j] ? temp[i++] : temp[j++];
    if (i == offset) mem_copy(arr + k, temp + j, n - j);
    else mem_copy(arr + k, temp + i, offset - i);
    delete[] temp;
}

void merge_sort(int arr[], const int n)
{
    if (n <= 1)return;
    auto offset = n / 2;
    merge_sort(arr, offset);
    merge_sort(arr + offset, n - offset);
    merge(arr, n, offset);
}

int partition_extra(int arr[], int const n)
{
    auto temp = new int[n];
    int i = 0, j = n - 1;
    for (int k = 1; k < n; k++)
    {
        if (arr[k] < arr[0])temp[i++] = arr[k];
        else temp[j--] = arr[k];
    }
    temp[i] = arr[0];
    mem_copy(arr, temp, n);
    delete[] temp;
    return i;
}

int partition_in_place(int arr[], const int n)
{
    int i = 1, j = n - 1;
    while (true)
    {
        while (i < n && arr[i] < arr[0])i++;
        while (j > 0 && arr[j] >= arr[0])j--;
        if (i < j)swap(arr[i], arr[j]);
        else break;
    }
    swap(arr[0], arr[j]);
    return j;
}

void quick_sort(int arr[], const int n, int (*fn)(int *, const int))
{
    if (n <= 1)return;
    int pivotat = rand() % n;
    swap(arr[pivotat], arr[0]);
    pivotat = fn(arr, n);
    quick_sort(arr, pivotat, fn);
    quick_sort(arr + pivotat + 1, n - 1 - pivotat, fn);
}

void quick_sort_extra(int arr[], const int n)
{
    quick_sort(arr, n, partition_extra);
}

void quick_sort_in_place(int arr[], const int n)
{
    quick_sort(arr, n, partition_in_place);
}
