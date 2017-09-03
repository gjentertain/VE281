//
// Created by liu on 17-9-3.
//

#include "selection.h"
#include <algorithm>
#include <iostream>

using namespace std;

int main()
{
    srand48(time(0));
    const int SIZE = 10000;
    int arr[SIZE] = {};
    int sorted[SIZE] = {};
    for (int i = 0; i < SIZE; i++)
    {
        sorted[i] = arr[i] = mrand48();
    }

    sort(sorted, sorted + SIZE);

    for (int i = 0; i < SIZE; i++)
    {
        auto item = random_selection(arr, SIZE, i);
        if (item != sorted[i])
        {
            cout << i << endl;
        }
    }

}

