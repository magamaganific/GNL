#include "get_next_line.h"
#include <stdio.h>

int main(void)
{
	char *line = NULL;
	int fd = open("hello", O_RDONLY);

	int i = 0;

	while (i < 10)
	{
		line = get_next_line(fd);
		printf("$%s", line);
		free(line);
		line = NULL;
		i++;
	}
}