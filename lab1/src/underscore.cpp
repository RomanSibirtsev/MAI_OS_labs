#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>


int main (int argc, char** argv) {
    char ch;
    int fd = std::atoi(argv[1]);
    (void)argc;
    while(true) {
        std::cin.get(ch);
        if (ch == ' ') {
            ch = '_';
        }
        write(fd, &ch, sizeof(ch));
    }
}
