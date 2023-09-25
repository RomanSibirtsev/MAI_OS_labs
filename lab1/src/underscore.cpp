#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>


int main (int argc, char** argv) {
    char ch;
    int fd = std::atoi(argv[1]);
    std::cout << "fd_2_child = " << argv[1] << std::endl;
    while(1) {
        std:: cin >> ch;
        write(fd, &ch, sizeof(ch));
    }


}
