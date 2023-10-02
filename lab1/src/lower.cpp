#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main (int argc, char** argv) {
    char ch;
    (void)argc;
    int fd = std::atoi(argv[1]);
    while(true) {
        read(fd, &ch, sizeof(ch));
        //std::cout << "ok" << std::endl;
        ch = (char) tolower(ch);
        std::cout << ch << std::flush;
    }
}