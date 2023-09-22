#include <iostream>
#include <string>
#include <unistd.h>

int main() {
    int status, fd1[2], fd2[2], connect[2];
    pid_t pid;
    std::string s;

    pipe(fd1);
    pipe(fd2);
    pipe(connect);

    pid = fork();
    if (pid == -1) {

    } else if (pid == 0) { // child 1
        close(connect[0]);
        close(fd1[1]);
        dup2(connect[1], STDOUT_FILENO);
        execlp();
    }
    pid = fork();
    if (pid == -1) {

    } else if (pid == 0) { // child 2
        close(connect[1]);
        close(fd2[0]);
        dup2(connect[0], STDIN_FILENO);
        execlp();
    }

    if (pid != 0) {

        while (std::cin >> s) {

        }
    }

    waitpid(-1, &status, 0);
    waitpid(-1, &status, 0);
    return 0;
}
