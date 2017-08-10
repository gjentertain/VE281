//
// Created by liu on 17-8-11.
//

#include <iostream>
#include <cstdlib>

using namespace std;

void bubble_sort(int arr[], int n)
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
        while (j >= 0)
        {
            if (arr[j] > temp) j--;
            else break;
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

void mem_copy(int dest[], const int src[], const int n)
{
    for (int i = 0; i < n; i++)
        dest[i] = src[i];
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

void merge_sort(int arr[], int n)
{
    if (n <= 1)return;
    auto offset = n / 2;
    merge_sort(arr, offset);
    merge_sort(arr + offset, n - offset);
    merge(arr, n, offset);
}

int main()
{
    int m, n;
    cin >> m >> n;
    auto arr = new int[n];
    switch (m)
    {
    case 0:
        bubble_sort(arr, n);
        break;
    case 1:
        insertion_sort(arr, n);
        break;
    case 2:
        selection_sort(arr, n);
        break;
    case 3:
        merge_sort(arr, n);
        break;
    case 4:
        break;
    case 5:
        break;
    default:
        break;
    }
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << endl;
    }
    delete[] arr;
    return 0;
}