#include <stdio.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <stdlib.h>

void	change(char *str)
{
	
}

int main(void)
{
	char		*str = "abcdefg";

	change(&str[2]);
	printf("%s\n", str);
	return (0);
}
