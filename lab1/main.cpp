#include <iostream>
#include <string>
#include <sys/wait.h>
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
        execlp("./lower.out", "./lower.out", std::to_string(fd1[0]).c_str(), 0);
    }
    pid = fork();
    if (pid == -1) {

    } else if (pid == 0) { // child 2
        close(connect[1]);
        close(fd2[0]);
        dup2(connect[0], STDIN_FILENO);
        execlp("./underscore.out", "./underscore.out", std::to_string(fd2[1]).c_str(), 0);
    }

    if (pid != 0) {
        close(fd1[0]);
        close(fd2[1]);
        char ch, ch2;
        while (std::cin >> s) {
            for (int i = 0; i < s.size(); ++i) {
                ch = s[i];
                write(fd1[1], &ch, sizeof(ch));
            }
            ch = '\n';
            write(fd1[1], &ch, sizeof(ch));
        }
        while(read(fd2[0], &ch2, sizeof(ch2))) {
            std::cout << ch2 << std::flush;
        }
    }

    waitpid(-1, &status, 0);
    waitpid(-1, &status, 0);
    return 0;
}
