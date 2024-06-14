#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define LOCK_FILE "/tmp/my_mutex.lock"

void acquire_lock() {
    while (access(LOCK_FILE, F_OK) != 0) {
        sleep(0.1);
    }
}
void release_lock() {
    unlink(LOCK_FILE);
}
void critical_section() {
    printf("Critical section entered by process %d\n", getpid());
    sleep(3); 
    printf("Critical section completed by process %d\n", getpid());
}

int main() {
    acquire_lock();

    critical_section();

    release_lock();

    return 0;
}