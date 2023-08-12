#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    printf("%d", open("main.cgdfgd", O_RDONLY));
}