#include "pipex.h"


int main()
{
		int fd = open("souleimane", O_RDONLY);
		char *str;
		int	i;
		i = 0;
		while((str = get_next_line(0)))
		{
			printf("%s\n", str);
			free(str);
		}
		free(str);
		// while (i < 1)
		// {
		// 	get_next_line(fd);
		// 	free(str);
		// 	i++;
		// }
}
	
