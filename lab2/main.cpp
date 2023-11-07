#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include "timsort.hpp"

int main()
{
    //int *arr = (int*)malloc(15 * sizeof(int));
    int arr[] = { -2, 7,  15,  -14, 0, 15,  0, 7,
                  -7, -4, -13, 5,   8, -14, 12 };
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Given Array is\n");
    printArray(arr, n);

    // Function Call
    timSort(arr, n);

    printf("After Sorting Array is\n");
    printArray(arr, n);
    return 0;
}