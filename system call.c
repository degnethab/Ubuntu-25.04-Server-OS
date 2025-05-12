#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main() {
    const char *file_path = "example.txt";
    int fd;
    struct stat sb;

    // Open the file
    fd = open(file_path, O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Get file size
    if (fstat(fd, &sb) == -1) {
        perror("fstat");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Memory-map the file
    char *mapped = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped == MAP_FAILED) {
        perror("mmap");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Modify the mapped memory
    strcpy(mapped, "Hello, mmap!");

    // Clean up
    if (munmap(mapped, sb.st_size) == -1) {
        perror("munmap");
    }

    close(fd);
    return 0;
}
