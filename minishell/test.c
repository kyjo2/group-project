#include <stdio.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (!dst || !src)
		return (0);
	if (dstsize == 0)
		return (src_len);
	i = 0;
	while (i < src_len && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = ' ';
	return (src_len);
}

#include <stdio.h>
#include <string.h>

int main() {
  char str[] = "memmove can be very useful";
  memmove(str + 25, "asdfasdfasddsfd", 11);
  puts(str);
  return 0;
}
