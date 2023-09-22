#include <iostream>
#include <string>
#include <unistd.h>

int main() {
    int status, fd1[2], fd2[2];
    pid_t pid;
    std::string s;

    pipe(fd1);
    pipe(fd2);

    pid = fork();
    if (pid == -1) {

    } else if (pid == 0) {
        execlp();
    }
    pid = fork();
    if (pid == -1) {

    } else if (pid == 0) {
        execlp();
    }

    while (std::cin >> s) {

    }

    waitpid(-1, &status, 0);
    waitpid(-1, &status, 0);
    return 0;
}
