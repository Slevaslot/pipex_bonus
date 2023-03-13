/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slevaslo <slevaslo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:12:02 by slevaslo          #+#    #+#             */
/*   Updated: 2023/03/13 17:21:52 by slevaslo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_bzero(void *ptr, size_t count)
{
	unsigned char	*str;
	size_t			i;

	str = ptr;
	i = 0;
	while (i < count)
	{
		str[i] = 0;
		i++;
	}
}

size_t	ft_strlen_for_gnl(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*get_next_line(int fd)
{
	static char		*left_line[4096];
	char			*line_retour;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (0);
	left_line[fd] = left_read(fd, left_line[fd]);
	if (!left_line[fd])
		return (NULL);
	line_retour = new_line(left_line[fd]);
	left_line[fd] = left_new_line(left_line[fd]);
	return (line_retour);
}

char	*left_read(int fd, char *ligne_retour)
{
	char	*buffer;
	int		ret;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE < 1)
		return (NULL);
	buffer = ft_calloc_for_gnl(sizeof(char), BUFFER_SIZE + 2);
	if (!buffer)
		return (NULL);
	ret = 1;
	while (ret != 0 && !ft_strchr_for_gnl(ligne_retour, '\n'))
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[ret] = '\0';
		ligne_retour = ft_strjoin_for_gnl(ligne_retour, buffer);
	}
	free (buffer);
	return (ligne_retour);
}

// #include <stdio.h>
// int main()
// {
// 		// int fd = open("souleimane", O_RDONLY);
// 		char *str;
// 		int	i;
// 		i = 0;
// 		while((str = get_next_line(0)))
// 		{
// 			printf("%s\n", str);
// 			free(str);
// 		}
// 		free(str);
// 		// while (i < 1)
// 		// {
// 		// 	get_next_line(fd);
// 		// 	free(str);
// 		// 	i++;
// 		// }
// }
