#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main (int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Wrong argc in lower.out\n";
        exit(-6);
    }
    char chLow;
    (void)argc;
    int fd = std::atoi(argv[1]);
    while(true) {
        read(fd, &chLow, sizeof(chLow));
        if(chLow == '\0') {
            break;
        }
        chLow = (char)tolower(chLow);
        std::cout << chLow << std::flush;
    }
    std::cout << '\0';
}