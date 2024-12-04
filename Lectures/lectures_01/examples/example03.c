#include <stddef.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>

int
main(void)
{
    int        c;
    while ((c = getc(stdin)) != EOF)
        if (putc(c, stdout) == EOF)
            perror("output error");
    if (ferror(stdin))
        perror("input error");
    exit(0);
}
