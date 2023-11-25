#include "parent.hpp"
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>     
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>

// void CreatePipe(int *fd) {
//     int status;
//     status = pipe(fd);
//     if (status == -1) {
//         std::cerr << "Failed pipe()\n";
//         exit(-1);
//     }
// }

sem_t* OpenSemaphore(const char *name, int value) {
    sem_t *semptr = sem_open(name, O_CREAT, S_IRUSR | S_IWUSR, value);
    if (semptr == SEM_FAILED){
        perror("Couldn't open the semaphore");
        exit(EXIT_FAILURE);
    }
    return semptr;
}

int CreateShm(const char* name) {
    int fd = shm_open(name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        std::cerr << "Failed shm_open\n";
        exit(-1);
    }
    ftruncate(fd, 1024);
    return fd;
}

char* MapSharedMemory(const int size, int fd) {
    char *memptr = (char*)mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (memptr == MAP_FAILED) {
        perror("Error with file mapping");
        exit(EXIT_FAILURE);
    }
    return memptr;
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

    char* name1 = "/shm1";
    sem_t *semptr1 = OpenSemaphore("SEMAPHORE_NAME_1", 0);
    int shd_fd1 = CreateShm(name1);
    char *memptr1 = MapSharedMemory(1024, shd_fd1); //MAP_SIZE = 1024

    child1 = getenv("PATH_CHILD1");
    child2 = getenv("PATH_CHILD2");


    // CreatePipe(fd1);
    // CreatePipe(fd2);
    // CreatePipe(connect);

    pid = CreateFork();
    if (pid == 0) { // child 1
        if (execlp(child1, "lower.out", name1, nullptr) == -1) {
            std::cerr << "Failed execlp()\n";
            exit(-5);
        }
    }
    // pid = CreateFork();
    // if (pid == 0) { // child 2
    //     if (execlp(child2, "underscore.out", std::to_string(fd2[1]).c_str(), nullptr) == -1) {
    //         std::cerr << "Failed execlp()\n";
    //         exit(-5);
    //     }
    // }

    if (pid != 0) {
        while (std::getline(std::cin, line)) {
            line += '\n';
            strcpy(memptr1, line.c_str());
            sem_post(semptr1);
            // std::cout << line << std::endl;
        }
    }

    waitpid(-1, &status, 0);
    waitpid(-1, &status, 0);
    return 0;
}
