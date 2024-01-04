#include "lib.hpp"
#include <iostream>
#include <vector>

extern "C" int PrimeCount(int a, int b) {
    std::vector<bool> prime(b + 1, true);
    prime[0] = prime[1] = false;
    for (int i = 2; i * i <= b + 1; ++i) {
        for (int j = i * i; j <= b + 1; j += i) {
            prime[j] = false;
        }
    }
    int count = 0;
    for (int i = a; i <= b; ++i) {
        if (prime[i]) {
            ++count;
        }
    }
    return count;
}
extern "C" int GCF(int a, int b) {
    int res = 0;
    for (int i = std::min(a, b); i > 0; --i) {
        if (a % i == 0 && b % i == 0) {
            res = i;
        }
    }
    return res;
}