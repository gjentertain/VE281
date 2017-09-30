//
// Created by liu on 17-9-3.
//

#ifndef P2_SELECTION_H
#define P2_SELECTION_H

#include <iostream>
#include <cstdlib>

typedef int data_type;
typedef unsigned int size_type;
typedef std::pair<data_type, size_type> pair_type;

data_type random_selection(pair_type arr[], const size_type n, const size_type order);

data_type deterministic_selection(pair_type arr[], const size_type n, const size_type order);

#endif //P2_SELECTION_H
