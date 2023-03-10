/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slevaslo <slevaslo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:48:01 by slevaslo          #+#    #+#             */
/*   Updated: 2023/03/10 19:11:06 by slevaslo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_process(char *str, char **envp)
{
	char	**mycmdargs;
	char	*path;

	mycmdargs = ft_split(str, ' ');
	if (!mycmdargs)
		return (ft_freetab(mycmdargs));
	path = find_path(mycmdargs[0], envp);
	if (!path)
		not_find(mycmdargs);
	execve(path, mycmdargs, envp);
}

void	dupncloses(int i, int pipes[2], data *data)
{
	if (i == 0)
	{
		dup2(data->fd_in, STDIN_FILENO);
		dup2(pipes[1], STDOUT_FILENO);
		close(data->fd_in);
		close(pipes[1]);
	}
	else if (i == data->cmds - 1)
	{
		dup2(data->prev, STDIN_FILENO);
		dup2(data->fd_out, STDOUT_FILENO);
		close(data->prev);
	}
	else
	{
		dup2(data->prev, STDIN_FILENO);
		dup2(pipes[1], STDOUT_FILENO);
		close(pipes[1]);
	}
	close(pipes[0]);
}

void	savencloses(int i, int pipes[2], data *data)
{
	if (i != data->cmds - 1)
	{
		if (data->prev != -1)
			close(data->prev);
		data->prev = pipes[0];
	}
	else
	{
		close(data->prev);
		close(pipes[0]);
	}
}

void	process(char **argv, char **envp, data *data)
{
	int	i;
	int	pid;
	int	pipes[2];

	i = 0;
	if (data->here_doc == 1)
		i++;
	while (i < data->cmds)
	{
		pipe(pipes);
		pid = fork();
		if (pid == -1)
			error();
		else if (pid == 0)
		{
			dupncloses(i, pipes, data);
			exec_process(argv[i + 2], envp);
		}
		close(pipes[1]);
		savencloses(i, pipes, data);
	i++;
	}
	waitpid(pid, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	data	data;

	if (argc < 5)
	{
		ft_putstr_fd("\033[31;5mError\033[0m Usage: ", 1);
		ft_putstr_fd("<infile> cmd1 | cmd2 | ... | cmdN > <outfile>\n", 1);
		exit(EXIT_FAILURE);
	}
	data.prev = -1;
	data.fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		data.fd_in = here_doc(argv[2]);
		data.here_doc = 1;
	}
	else
	{
		data.fd_in = open(argv[1], O_RDONLY);
		data.here_doc = 0;
	}
	data.cmds = argc - 3 + data.here_doc;
	if (data.fd_out == -1 || data.fd_in == -1)
		error();
	process(argv, envp, &data);
	close(data.fd_in);
	close(data.fd_out);
	return (0);
}
