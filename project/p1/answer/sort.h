//
// Created by liu on 17-8-30.
//

#ifndef P1_SORT_H
#define P1_SORT_H

#include <cstdlib>

typedef int32_t data_type;
typedef u_int32_t size_type;

void bubble_sort(data_type arr[], const size_type n);

void insertion_sort(data_type arr[], const size_type n);

void selection_sort(data_type arr[], const size_type n);

void merge_sort(data_type arr[], const size_type n);

void quick_sort_extra(data_type arr[], const size_type n);

void quick_sort_in_place(data_type arr[], const size_type n);

#endif //P1_SORT_H
