#include "../get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(void)
{
    int fd = open("test/file.txt", O_RDONLY);
    if (fd < 0) {
        printf("Problem with opening a file\n");
        return 1;
    }
    int i = 0;
    while (1) {
        char *line = get_next_line(fd);
        if (!line) {
            printf("[%i] %s",i,line);
            break;
        }
        printf("[%i] %s",i,line);
        free(line);
        i++;
    }
    return 0;
}
