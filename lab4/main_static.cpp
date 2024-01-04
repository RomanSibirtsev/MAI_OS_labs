#include <iostream>
#include "lib.hpp"

int main() {
    std::string command;
    int a, b;

    while (true) {
        std::cin >> command;
        if (command == "0") {
            break;
        } else if (command == "1") {
            std::cin >> a >> b;
            std::cout << "PrimeCount = " << PrimeCount(a, b) << std::endl;
        } else if (command == "2") {
            std::cin >> a >> b;
            std::cout << "GCF = " << GCF(a, b) << std::endl;
        } else {
            std::cout << "Wrong Argument" << std::endl;
        }
    }
}