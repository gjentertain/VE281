//
// Created by liu on 17-9-3.
//

#include "selection.h"
#include <algorithm>
#include <iostream>

using namespace std;

int main()
{
    const int selection_fns_num = 2;
    data_type (*const selection_fns[selection_fns_num])(const data_type *, const size_type, const size_type) = {
            random_selection,
            deterministic_selection
    };
    int m;
    size_type n, o;
    cin >> m;
    if (m >= 0 && m < selection_fns_num)
    {
        cin >> n >> o;
        auto arr = new data_type[n];
        for (size_type i = 0; i < n; i++)
        {
            cin >> arr[i];
        }
        auto result = selection_fns[m](arr, n, o);
        cout << "The order-" << o << " item is " << result << endl;
        delete[] arr;
    }
    return 0;

/*
    srand48(time(0));
    const int SIZE = 1000;
    int arr[SIZE] = {};
    int sorted[SIZE] = {};
    for (int i = 0; i < SIZE; i++)
    {
        sorted[i] = arr[i] = mrand48();
    }

    sort(sorted, sorted + SIZE);

    for (int i = 0; i < SIZE; i++)
    {
        auto item = deterministic_selection(arr, SIZE, i);
        if (item != sorted[i])
        {
            cout << i << endl;
        }
    }
*/

}

