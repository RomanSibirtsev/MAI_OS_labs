#include "utils.hpp"

int main (int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Wrong argc in underscore.out\n";
        exit(-6);
    }

    const char* fileName = argv[1];
    const char* fileName2 = argv[2];

    sem_t *semptr1 = CreateSemaphore(SEM_2, 0);
    int shd_fd1 = CreateShm(fileName);
    char *memptr1 = MapSharedMemory(FILE_SIZE, shd_fd1);

    sem_t *semptr2 = CreateSemaphore(SEM_3, 0);
    int shd_fd2 = CreateShm(fileName2);
    char *memptr2 = MapSharedMemory(FILE_SIZE, shd_fd2);

    while(true) {
        sem_wait(semptr1);
        std::string_view st(memptr1);
        std::string s = {st.begin(), st.end()};
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == ' ') {
                s[i] = '_';
            }
        }
        
        if (s != "\n")  {
            strcpy(memptr2, s.c_str());
            strcpy(memptr1, "\n");
            sem_post(semptr2);
        }

        if (s == "\0") {
            break;
        }
    }

    sem_close(semptr1);
    sem_unlink(SEM_2);
    shm_unlink(fileName);
    munmap(memptr1, FILE_SIZE);
    close(shd_fd1);

    sem_close(semptr2);
    sem_unlink(SEM_3);
    shm_unlink(fileName2);
    munmap(memptr2, FILE_SIZE);
    close(shd_fd2);

}
