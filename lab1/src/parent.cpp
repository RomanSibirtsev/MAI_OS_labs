#include "parent.hpp"

int parentWork() {
    int status, fd1[2], fd2[2], connect[2], capacity;
    pid_t pid;
    std::string s;

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
        char ch, ch2, end = '\0';
        while (std::getline(std::cin, s)) {
            for (size_t i = 0; i < s.size(); ++i) {
                ch = s[i];
                write(fd1[1], &ch, sizeof(ch));
            }
            ch = '\n';
            write(fd1[1], &ch, sizeof(ch));

            capacity = s.size();
            while(true) {
                read(fd2[0], &ch2, sizeof(ch2));
                --capacity;
                std::cout << ch2 << std::flush;
                if (capacity == -1) break;
            }
        }
        write(fd1[1], &end, sizeof(end));
    }

    waitpid(-1, &status, 0);
    waitpid(-1, &status, 0);
    return 0;
}
