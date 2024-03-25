#include <fcntl.h>
#include <stdio.h>

int main() {
    int fd;

    fd = open("TEXT.TXT", O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    printf("The file descriptor for TEXT.TXT is %d\n", fd);

    close(fd); // Always remember to close the file descriptor when you're done with it

    return 0;
}