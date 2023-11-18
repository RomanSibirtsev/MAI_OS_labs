#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include "timsort.hpp"
#include <chrono>

using namespace std::chrono;

int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cout << "Not enough arguments" << std::endl;
        return -1;
    }

    //int *arr = (int*)malloc(15 * sizeof(int));
    int arr[] = { -2, 7,  15,  -14, 0, 15,  0, 7,
                  -7, -4, -13, 5,   8, -14, 12 };
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Given Array is\n");
    printArray(arr, n);

    int maxThreads = std::atol(argv[1]);
    std::cout << "arg = " << maxThreads << std::endl;
    // Function Call
    auto start = high_resolution_clock::now();
    timSort(arr, n, maxThreads);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << duration.count() << std::endl;

    printf("After Sorting Array is\n");
    printArray(arr, n);
    return 0;
}