//
// Created by liu on 17-9-3.
//

#ifndef P1_SELECTION_WRAPPER_H
#define P1_SELECTION_WRAPPER_H

#include <algorithm>
#include "../answer/selection.h"

data_type cpp_selection(data_type arr[], const size_type n, const size_type order) {
    std::nth_element(arr, arr + order, arr + n);
    return arr[order];
}

data_type (*const selection_fns[])(data_type *, const size_type, const size_type) = {
        random_selection,
        deterministic_selection,
        cpp_selection,
};

#endif //P1_SELECTION_WRAPPER_H
