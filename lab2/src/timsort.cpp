#include "timsort.hpp"
#include <cmath>

const int RUN = 4;

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

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d  ", arr[i]);
    printf("\n");
}

void* insertionSort(void* args)
{
    const auto &ar = *(Args1*)args;
    int *arr = ar.arr;
    int left = ar.left;
    int right = ar.right;
    for (int i = left + 1; i <= right; i++) {
        int temp = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }

    // sleep(50);
    pthread_exit(0);
}

void* merge(void* args)
{
    Args2 arg = *(Args2*)args;
    int* arr = arg.arr;
    int m = arg.m;
    int r = arg.r;
    int l = arg.l;

    int len1 = m - l + 1, len2 = r - m;
    int left[len1], right[len2];
    for (int i = 0; i < len1; i++)
        left[i] = arr[l + i];
    for (int i = 0; i < len2; i++)
        right[i] = arr[m + 1 + i];

    int i = 0;
    int j = 0;
    int k = l;

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

    while (i < len1) {
        arr[k] = left[i];
        k++;
        i++;
    }

    while (j < len2) {
        arr[k] = right[j];
        k++;
        j++;
    }

    // sleep(50);
    pthread_exit(0);
}

void timSort(int *arr, int n, int maxThreads)
{

    int threadCount = std::min(n / RUN + 1, maxThreads);
    if (maxThreads == -1) {
        threadCount = n / RUN + 1;
    }
    pthread_t tid[threadCount];
    int j = 0;
    for (int i = 0; i < n; i += RUN)
    {        
        Args1* arg = new Args1;
        arg->arr = arr;
        arg->left = i;
        arg->right = std::min((i + RUN - 1), (n - 1));
        // insertionSort((void*)(&arg));
        if (j < threadCount) {
            pthread_create(&tid[j++], nullptr, insertionSort, (void*)(arg));
        } else {
            while (j > 0) {
                pthread_join(tid[--j], NULL);
            }
            ++j;
            pthread_create(&tid[j++], nullptr, insertionSort, (void*)(arg));
        }
    }

    while (j > 0) {
        pthread_join(tid[--j], NULL);
    }

    std::vector<pthread_t> tid2(threadCount);
    j = 0;
    for (int size = RUN; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = std::min((left + 2 * size - 1), (n - 1));
            if (mid < right) {
                Args2* arg = new Args2;
                arg->arr = arr;
                arg->l = left;
                arg->m = mid;
                arg->r = right;
                // merge((void*)arg);
                if (j < threadCount) {
                    pthread_create(&tid2[j++], nullptr, merge, (void*)(arg));
                } else {
                    while (j > 0) {
                        pthread_join(tid2[--j], NULL);
                    }
                    pthread_create(&tid2[j++], nullptr, merge, (void*)(arg));
                }
            }
        }
    }

    while (j > 0) {
        pthread_join(tid2[--j], NULL);
    }
}
