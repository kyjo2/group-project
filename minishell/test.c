#include <stdio.h>
#include <unistd.h>
#include <sys/fcntl.h>

int main(void)
{
	int fd1;
	int fd2;
	int fd3;

	fd1 = open("a",O_RDONLY);
	fd2 = dup(fd1);
	fd3 = dup2(fd2, 5);
	printf("fd1:%d fd2:%d\n", fd1, fd2);
	printf("fd3:%d\n", fd3);
	close(fd1);
	close(fd2);
}