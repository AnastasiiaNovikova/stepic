#include <iostream>
#include <pthread.h>

void *func(void *) {
    std::cout << "Hello from thread" << std::endl;

    while(1);

    return NULL;
}

int main() {
    pthread_t thread;
    void * res;
    int s;

    if( pthread_create(&thread, NULL, func, NULL) != 0) {
        std::cerr << "Error creating thread\n";
    }
    if( pthread_join(thread, &res) != 0 ) {
        std::cerr << "Error joining thread\n";
    }

    return 0;
}
