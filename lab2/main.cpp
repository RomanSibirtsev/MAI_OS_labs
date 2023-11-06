#include <iostream>
#include <pthread.h>
#include <unistd.h>

int sum = 0;

void* increment_function_plus_200(void* args) {
    for (int i=0; i<100; i++)
    {
        sum = sum + 2;
    }
    sleep(50);
    pthread_exit(0);
}

int main() {
    const int threadCount = 1000;
    pthread_t tid[threadCount];
    for (int i=0; i<threadCount; i++)
    {
        pthread_create(&tid[i], NULL, increment_function_plus_200, NULL);
    }
    for (int i=0; i<threadCount; i++)
    {
        pthread_join(tid[i], NULL);
    }
    std::cout << "sum = " << sum << std::endl;
    return 0;
}