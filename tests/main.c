#include "../get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(void)
{
    int fd = open("files/example", O_RDONLY);
    if (fd < 0) {
        printf("problem\n");
        return 1;
    }
    int i = 0;
    while (1) {
        char *line = get_next_line(fd);
        if (!line) {
            break;
        }
        printf("[%i] %s!",i,line);
        free(line);
        i++;
    }
    return 0;
}
