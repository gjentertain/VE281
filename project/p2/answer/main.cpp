//
// Created by liu on 17-9-3.
//

#include "selection.h"

using namespace std;

int main() {

    const int selection_fns_num = 2;
    data_type (*const selection_fns[selection_fns_num])(pair_type *, const size_type, const size_type) = {
            random_selection,
            deterministic_selection
    };
    int m;
    size_type n, o;
    cin >> m;
    if (m >= 0 && m < selection_fns_num) {
        cin >> n >> o;
        auto arr = (pair_type *) malloc(n * sizeof(pair_type));
        for (size_type i = 0; i < n; i++) {
            cin >> arr[i].first;
            arr[i].second = i;
        }
        auto result = selection_fns[m](arr, n, o);
        cout << "The order-" << o << " item is " << result << endl;
        free(arr);
    }
    return 0;
}

