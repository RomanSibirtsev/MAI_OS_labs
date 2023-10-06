#include "parent.hpp"

void CreatePipe(int *fd) {
    int status;
    status = pipe(fd);
    if (status == -1) {
        std::cerr << "Failed pipe()\n";
        exit(-1);
    }
}

int CreateFork() {
    int pid;
    pid = fork();
    if (pid == -1) {
        std::cerr << "Failed fork()\n";
        exit(-2);
    }
    return pid;
}

void DoClose(int fd) {
    int status;
    status = close(fd);
    if (status == -1) {
        std::cerr << "Failed close()\n";
        exit(-3);
    }
}

void DoDup(int a, int b) {
    int status;
    status = dup2(a, b);
    if (status == -1) {
        std::cerr << "Failed dup2()\n";
        exit(-4);
    }
}

int ParentWork() {
    pid_t pid;
    int status;
    int capacity = 0;
    int fd1[2];
    int fd2[2];
    int connect[2];
    char *child1;
    char *child2;
    std::string line;

    child1 = getenv("PATH_CHILD1");
    child2 = getenv("PATH_CHILD2");

    CreatePipe(fd1);
    CreatePipe(fd2);
    CreatePipe(connect);

    pid = CreateFork();
    if (pid == 0) { // child 1
        DoClose(connect[0]);
        DoClose(fd1[1]);
        DoDup(connect[1], STDOUT_FILENO);
        if (execlp(child1, "lower.out", std::to_string(fd1[0]).c_str(), nullptr) == -1) {
            std::cerr << "Failed execlp()\n";
            exit(-5);
        }
    }
    pid = CreateFork();
    if (pid == 0) { // child 2
        DoClose(connect[1]);
        DoClose(fd2[0]);
        DoDup(connect[0], STDIN_FILENO);
        if (execlp(child2, "underscore.out", std::to_string(fd2[1]).c_str(), nullptr) == -1) {
            std::cerr << "Failed execlp()\n";
            exit(-5);
        }
    }

    if (pid != 0) {
        DoClose(fd1[0]);
        DoClose(fd2[1]);
        char chWrite;
        char end = '\0';
        char toOut[256];
        int readCount;
        while (std::getline(std::cin, line)) {
            write(fd1[1], line.c_str(), line.size());

            chWrite = '\n';
            write(fd1[1], &chWrite, sizeof(chWrite));

            capacity += line.size() + 1;
        }
        write(fd1[1], &end, sizeof(end));

        while(capacity > 0) {
            readCount = read(fd2[0], toOut, sizeof(toOut));
            if (readCount != -1) {
                capacity -= readCount;
            }
            //std::cout << toOut << std::flush;
            for (int i = 0; i < readCount; ++i) {
                std::cout << toOut[i] << std::flush;
            }   
        }
    }

    waitpid(-1, &status, 0);
    waitpid(-1, &status, 0);
    return 0;
}
