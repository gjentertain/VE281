//
// Created by liu on 17-8-11.
//

#include <cstdlib>
#include <iostream>
#include "sort.h"

using namespace std;

int main()
{
    void (*const sort_fns[6])(int *, const int) = {
            bubble_sort,
            insertion_sort,
            selection_sort,
            merge_sort,
            quick_sort_extra,
            quick_sort_in_place
    };
    int m, n;
    cin >> m;
    if (m >= 0 && m <= 5)
    {
        cin >> n;
        auto arr = new int[n];
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
        }
        sort_fns[m](arr, n);
        for (int i = 0; i < n; i++)
        {
            cout << arr[i] << endl;
        }
        delete[] arr;
    }
    return 0;
}