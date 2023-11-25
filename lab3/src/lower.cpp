#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>     
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>

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

int main (int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Wrong argc in lower.out\n";
        exit(-6);
    }
    const char* fileName = argv[1];

    //char chLow;
    // int fd = std::atoi(argv[1]);
    sem_t *semptr1 = OpenSemaphore("SEMAPHORE_NAME_1", 0);
    int shared_memory_fd1 = CreateShm(fileName);
    char *memptr1 = MapSharedMemory(1024, shared_memory_fd1);
    char f[1024] = "";
    //std::ofstream fout(fileName, std::ios::app);
    while(true) {
        sem_wait(semptr1);
        //if(std::getline(fin, s)) break;
        std::string_view st(memptr1);
        //strcpy(memptr1, "*");
        std::string s = {st.begin(), st.end()};
        for (int i = 0; i < s.size(); ++i) {
            s[i] = (char)tolower(s[i]);
        }
        if (s != "\n")  {
            std::cout << "S = " << s;
            strcpy(memptr1, "\n");
        }
    }
    // std::cout << '\0';
}