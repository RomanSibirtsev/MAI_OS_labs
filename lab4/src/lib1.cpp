#include "lib.hpp"
#include <iostream>
extern "C" bool IsPrime(int a) {
    bool res = 1;
    for (int i = 2; i < a; ++i) {
        if (a % i == 0) {
            res = 0;
        }
    }
    return res;
} 

extern "C" int PrimeCount(int a, int b) {
    int count = 0;
    for (int i = a; i <= b; ++i) {
        if (IsPrime(i)) {
            ++count;
        }
    }
    return count;
}
extern "C" int GCF(int a, int b) {
    while (a != 0 && b != 0) {
        if (a > b) {
            a = a % b;
        } else {
            b = b % a;
        }
    }
    return a + b;
}