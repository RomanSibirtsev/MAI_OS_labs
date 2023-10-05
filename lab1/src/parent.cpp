#include "parent.hpp"

int ParentWork() {
    pid_t pid;
    int status;
    int capacity;
    int fd1[2];
    int fd2[2];
    int connect[2];
    std::string line;

    pipe(fd1);
    pipe(fd2);
    pipe(connect);

    pid = fork();
    if (pid == -1) {
        std::cerr << "Failed fork()\n";
    } else if (pid == 0) { // child 1
        close(connect[0]);
        close(fd1[1]);
        dup2(connect[1], STDOUT_FILENO);
        execlp("./lower.out", "./lower.out", std::to_string(fd1[0]).c_str(), NULL);
    }
    pid = fork();
    if (pid == -1) {
        std::cerr << "Failed fork()\n";
    } else if (pid == 0) { // child 2
        close(connect[1]);
        close(fd2[0]);
        dup2(connect[0], STDIN_FILENO);
        execlp("./underscore.out", "./underscore.out", std::to_string(fd2[1]).c_str(), NULL);
    }

    if (pid != 0) {
        close(fd1[0]);
        close(fd2[1]);
        char chWrite;
        char chOut;
        char end = '\0';
        while (std::getline(std::cin, line)) {
            for (char i : line) {
                chWrite = i;
                write(fd1[1], &chWrite, sizeof(chWrite));
            }
            chWrite = '\n';
            write(fd1[1], &chWrite, sizeof(chWrite));

            capacity = line.size();
            while(true) {
                read(fd2[0], &chOut, sizeof(chOut));
                --capacity;
                std::cout << chOut << std::flush;
                if (capacity == -1) {
                    break;
                }
            }
        }
        write(fd1[1], &end, sizeof(end));
    }

    waitpid(-1, &status, 0);
    waitpid(-1, &status, 0);
    return 0;
}
