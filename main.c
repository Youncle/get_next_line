
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

/* main for testing 1 fd */
int		main(int argc, char **argv)
{
	int fd;
	char *line;
	int ret;/* printing gnl return value*/
	int i;

	if (argc >= 2)
	{
		if (access(argv[1], F_OK) == 0)
		{
			i = 0;
			fd = open(argv[1], O_RDONLY);
			while((ret = get_next_line(fd, &line)) == 1)
			{
				i++;
				printf("MAIN:%d, line>%s\n", ret, line);
			}
			close(fd);
       	}
	}
}
