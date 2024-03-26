#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024
#endif

typedef unsigned long long  t_type_t;

char *get_next_line(int fd)
{
    static char remainder[BUFFER_SIZE + 1] = {0};
    char *buf;
    char *newline_pos;
    ssize_t bytes_read;

    buf = malloc(BUFFER_SIZE + 1);
    while ((newline_pos = strchr(remainder, '\n')) == NULL)
    {
        bytes_read = read(fd, buf, BUFFER_SIZE);
        if (bytes_read <= 0)
            break;
        buf[bytes_read] = '\0';
        strncat(remainder, buf, bytes_read);
    }
    free(buf);

    char *line = NULL;
    if (newline_pos != NULL)
    {
        *newline_pos = '\0';
        line = strdup(remainder);
        memmove(remainder, newline_pos + 1, strlen(newline_pos + 1) + 1);
    }
    else if (strlen(remainder) > 0)
    {
        line = strdup(remainder);
        remainder[0] = '\0';
    }

    return line;
}

int main()
{
    char *tp;
    int fd;

    fd = open("TEXT.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    tp = get_next_line(fd);
    printf("whatevs %s", tp);

    close(fd); // Don't forget to close the file when you're done with it

    return 0;
}