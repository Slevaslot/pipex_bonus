/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slevaslo <slevaslo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:38:08 by slevaslo          #+#    #+#             */
/*   Updated: 2023/03/10 19:16:34 by slevaslo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*path_is_ok(char **paths, char *cmd)
{
	char	*fpath;
	char	*part_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		if (!part_path)
			return (free(part_path), NULL);
		fpath = ft_strjoin(part_path, cmd);
		free(part_path);
		if (!fpath)
			return (free(fpath), NULL);
		if (access(fpath, F_OK) == 0)
			return (fpath);
		free(fpath);
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	int		i;
	char	*str;

	i = 0;
	if (access(cmd, F_OK) == 0)
			return (cmd);
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (ft_freetab(paths), NULL);
	i = 0;
	str = path_is_ok(paths, cmd);
	ft_freetab(paths);
	if (!str)
		return (NULL);
	return (str);
}

int	here_doc(char *limit)
{
	char	*buffer;
	int		here_doc[2];

	pipe(here_doc);
	limit = ft_strjoin(limit, "\n");
	if (!limit)
		return(free(limit), 0);
	buffer = get_next_line(0);
	while (1)
	{
		buffer = get_next_line(0);
		if(ft_strncmp(buffer, limit, ft_strlen(limit)) == 0)
			break ;
		ft_putstr_fd(buffer, here_doc[1]);
	}
	close(here_doc[0]);
	return (here_doc[0]);
}


char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

void	error(void)
{
	perror("\033[31;5mError\033[0m ");
	exit(EXIT_FAILURE);
}

void	not_find(char **mycmdargs)
{
	ft_putstr_fd("zsh: command not found: ", 2);
	ft_putstr_fd(mycmdargs[0], 2);
	ft_putstr_fd("\n", 2);
	ft_freetab(mycmdargs);
	exit(EXIT_FAILURE);
}
