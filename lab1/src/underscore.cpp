#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main (int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Wrong argc in underscore.out\n";
        exit(-6);
    }
    char ch;
    int fd = std::atoi(argv[1]);
    (void)argc;
    while(true) {
        std::cin.get(ch);
        if (ch == ' ') {
            ch = '_';
        } else if (ch == '\0') {
            break;
        }
        write(fd, &ch, sizeof(ch));
    }
}
