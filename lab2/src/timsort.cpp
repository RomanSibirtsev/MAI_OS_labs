// C++ program to perform TimSort.
#include <bits/stdc++.h>
using namespace std;
const int RUN = 2;

// This function sorts array from left
// index to to right index which is
// of size atmost RUN

struct Args1 {
    int* arr;
    int left;
    int right;
};

struct Args2 {
    int* arr;
    int l;
    int m;
    int r;
};

void* insertionSort(void* args)
{
    //Args1 ar = *((Args1*)args);
    const auto &ar = *(reinterpret_cast<Args1 *>(args));
    int *arr = ar.arr;
    int left = ar.left;
    int right = ar.right;
    //int* arr = ar.arr;
    //std::cout <<"left = " <<  left << ' ' << right << ' ';
    //int arr[], int left, int right
    for (int i = left + 1; i <= right; i++) {
        int temp = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
    //return nullptr;
    sleep(50);
    pthread_exit(0);
}

// Merge function merges the sorted runs
void* merge(void* args)
{
    Args2 arg = *(Args2*)args;
    int* arr = arg.arr;
    int m = arg.m;
    int r = arg.r;
    int l = arg.l;
    //int arr[], int l, int m, int r
    // Original array is broken in two
    // parts left and right array
    int len1 = m - l + 1, len2 = r - m;
    int left[len1], right[len2];
    for (int i = 0; i < len1; i++)
        left[i] = arr[l + i];
    for (int i = 0; i < len2; i++)
        right[i] = arr[m + 1 + i];

    int i = 0;
    int j = 0;
    int k = l;

    // After comparing, we
    // merge those two array
    // in larger sub array
    while (i < len1 && j < len2) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        }
        else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements of
    // left, if any
    while (i < len1) {
        arr[k] = left[i];
        k++;
        i++;
    }

    // Copy remaining element of
    // right, if any
    while (j < len2) {
        arr[k] = right[j];
        k++;
        j++;
    }
    //return nullptr;
    sleep(50);
    pthread_exit(0);
}

// Iterative Timsort function to sort the
// array[0...n-1] (similar to merge sort)
void timSort(int *arr, int n)
{

    // Sort individual subarrays of size RUN
    // for (int i = 0; i < n; i += RUN) {
    //     //insertionSort(arr, i, min((i + RUN - 1), (n - 1)));
    //     Args1 arg({arr, i,  min((i + RUN - 1), (n - 1))});
    //     insertionSort((void*)(&arg));

    // }
    const int threadCount = n / RUN + 1;
    pthread_t tid[threadCount];
    int j = 0;
    for (int i = 0; i < n; i += RUN)
    {
        Args1 arg({arr, i,  min((i + RUN - 1), (n - 1))});
    //     insertionSort((void*)(&arg));
        pthread_create(&tid[j++], nullptr, insertionSort, (void*)(&arg));
    }
    j = 0;
    for (int i = 0; i < n; i += RUN)
    {
        pthread_join(tid[j++], NULL);
    }

    // Start merging from size RUN (or 32).
    // It will merge
    // to form size 64, then 128, 256
    // and so on ....
    std::vector<pthread_t> tid2;
    j = 0;
    for (int size = RUN; size < n; size = 2 * size) {

        // pick starting point of
        // left sub array. We
        // are going to merge
        // arr[left..left+size-1]
        // and arr[left+size, left+2*size-1]
        // After every merge, we
        // increase left by 2*size
        for (int left = 0; left < n; left += 2 * size) {

            // Find ending point of
            // left sub array
            // mid+1 is starting point
            // of right sub array
            int mid = left + size - 1;
            int right = min((left + 2 * size - 1), (n - 1));

            // merge sub array arr[left.....mid] &
            // arr[mid+1....right]
            if (mid < right) {
                //merge(arr, left, mid, right);
                Args2 arg;
                arg.arr = arr;
                arg.l = left;
                arg.m = mid;
                arg.r = right;
                //merge((void*)arg);
                tid2.push_back(0);
                pthread_create(&tid2[j++], nullptr, merge, (void*)(&arg));
            }
        }
    }
    j = 0;
    for (int i = 0; i < tid2.size(); ++i)
    {
        pthread_join(tid2[j++], NULL);
    }
}

// Utility function to print the Array
void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d  ", arr[i]);
    printf("\n");
}

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