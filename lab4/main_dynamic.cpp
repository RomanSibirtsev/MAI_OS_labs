#include <iostream>
#include <cstdlib>
#include <dlfcn.h>

using PrimeCountFunc = int (*)(int, int);
using GCFFunc = int (*)(int, int);

void* loadLibrary(const std::string& libraryName) {
    void* handle = dlopen(libraryName.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << "Cannot load library: " << dlerror() << std::endl;
        exit(EXIT_FAILURE);
    }
    return handle;
}

void unloadLibrary(void* handle) {
    if (dlclose(handle) != 0) {
        std::cerr << "Cannot unload library: " << dlerror() << std::endl;
        exit(EXIT_FAILURE);
    }
}

int main() {
    int whichLib = 1;

    const char* PathToLib1 = getenv("PATH_TO_LIB1");
    const char* PathToLib2 = getenv("PATH_TO_LIB2");

    if (PathToLib1 == nullptr || PathToLib2 == nullptr) {
        std::cout << "PATH_TO_LIB1 or PATH_TO_LIB2 is not specified\n";
        exit(1);
    }

    void* libraryHandle = loadLibrary(PathToLib1);

    PrimeCountFunc PrimeCount = (PrimeCountFunc)dlsym(libraryHandle, "PrimeCount");
    GCFFunc GCF = (GCFFunc)dlsym(libraryHandle, "GCF");
    std::string command;

    while (true) {
        std::cin >> command;
        int a, b;
        if (command == "0") {
            unloadLibrary(libraryHandle);
            if (whichLib == 2) {
                libraryHandle = loadLibrary(PathToLib1);
                whichLib = 1;
            } else if (whichLib == 1) {
                libraryHandle = loadLibrary(PathToLib2);
                whichLib = 2;
            }
            PrimeCount = reinterpret_cast<PrimeCountFunc>(dlsym(libraryHandle, "PrimeCount"));
            GCF = reinterpret_cast<GCFFunc>(dlsym(libraryHandle, "GCF"));

        } else if (command == "1") {
            std::cin >> a >> b;
            std::cout << "OK\n";
            std::cout << "PrimeCount = " << PrimeCount(a, b) << std::endl;
        } else if (command == "2") {
            std::cin >> a >> b;
            std::cout << "OK\n";
            std::cout << "GCF = " << GCF(a, b) << std::endl;
        } else {
            std::cout << "Wrong Argument" << std::endl;
        }
    }

}