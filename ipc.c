
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PIPE_NAME "/tmp/mypipe"

void pembaca() {
    int fd;
    char buffer[1024];

    // Membuka named pipe untuk membaca
    fd = open(PIPE_NAME, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    while (1) {
        // Membaca dari named pipe
        ssize_t bytes_read = read(fd, buffer, 1024);
        if (bytes_read == -1) {
            perror("read");
            exit(1);
        }
        buffer[bytes_read] = '\0'; // Add null terminator
        printf("Pembaca menerima: %s\n", buffer);
    }

    close(fd);
}

void penulis() {
    int fd;
    char buffer[1024];

    // Membuka named pipe untuk menulis
    fd = open(PIPE_NAME, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    for (int i = 1; i <= 5; i++) {
        sprintf(buffer, "Pesan %d", i);
        ssize_t bytes_written = write(fd, buffer, strlen(buffer));
        if (bytes_written == -1) {
            perror("write");
            exit(1);
        }
        sleep(1);
    }

    close(fd);
}

int main() {
    // Membuat named pipe jika belum ada
    if (access(PIPE_NAME, F_OK) == -1) {
        mkfifo(PIPE_NAME, 0666);
    }

    // Menjalankan fungsi pembaca di background
    pid_t pid = fork();
    if (pid == 0) {
        pembaca();
    } else {
        penulis();
        wait(NULL);
        unlink(PIPE_NAME);
        printf("IPC selesai.\n");
    }

    return 0;
}
