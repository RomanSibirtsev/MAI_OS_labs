#include <iostream>
#include <algorithm>
#include <gtest/gtest.h>

#include "timsort.hpp"


void TestParent(int* base_arr) {
    int n = sizeof(base_arr) / sizeof(base_arr[0]);
    int arr_1[n], arr_2[n];
    std::copy(base_arr, base_arr + n, arr_1);
    std::copy(base_arr, base_arr + n, arr_2);

    timSort(arr_1, n, 5);
    std::sort(arr_2, arr_2 + n);

    for (int i = 0; i < n; ++i) {
        ASSERT_EQ(arr_1[i], arr_2[i]);
    }
}

TEST(SortTest, ONE) {
    int arr[] = { -2, 7, 15, -14, 0, 15, 0, 7, 234, 3, -89, 9, -12, 21,
                  -7, -4, -13, 5, 8, -14, 12, 54, 1, 0, 127, 40, 55};
    TestParent(arr);
}

TEST(SortTest, TWO) {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
                 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,};
    TestParent(arr);
}

TEST(SortTest, THREE) {
    int arr[] = {1, 2, -34, 45, -66, 2, 96, -9, 33, 1, 1, 90, 44, -34, -3, 4, 35, 0};
    TestParent(arr);
}