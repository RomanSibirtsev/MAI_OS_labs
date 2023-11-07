#include <iostream>
#include <algorithm>
#include <gtest/gtest.h>
#include "timsort.hpp"


TEST(cin_test, ONE) {
    int arr[] = { -2, 7, 15, -14, 0, 15, 0, 7, 234, 3, -89, 9, -12, 21,
                  -7, -4, -13, 5, 8, -14, 12, 54, 1, 0, 127, 40, 55};
    int n = sizeof(arr) / sizeof(arr[0]);

    int arr_2[n];
    std::copy(arr, arr + n, arr_2);

    std::sort(arr_2, arr_2 + n);
    timSort(arr, n);

    printArray(arr, n);
    printArray(arr_2, n);

    for (int i = 0; i < n; ++i) {
        ASSERT_EQ(arr[i], arr_2[i]);
    }
}