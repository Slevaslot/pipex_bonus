/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slevaslo <slevaslo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:47:35 by slevaslo          #+#    #+#             */
/*   Updated: 2023/03/10 19:12:09 by slevaslo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libftprintfgnl/libftprintfgnl.h"
#include <sys/types.h>
#include <sys/wait.h>

typedef struct data
{
	int prev;
	int cmds;
	int fd_out;
	int fd_in;
	int here_doc;
}
data;

// char	*ft_join(char *str, char *sep);
// void	pipexchar **str, char **str1);
void	exec_process(char *str, char **envp);
// char	*ft_substr(char const *s, unsigned int start, size_t len);
// char	**ft_split(char const *s, char c);
// int		ft_strlen(const char *str);
// char	*ft_strjoin(char const *s1, char const *s2);
// char	*ft_strnstr(const char *str, const char *to_find, size_t n);
// char	*ft_june(const char *str);
void	not_find(char **mycmdargs);
void	error(void);
int		here_doc(char *limit);
// char	*str_remove_whitespace(char *str);
// void	ft_putstr_fd(char *str, int fd);
// void	clearmem(char **str);
// void	close_pipes_dup2(int *pipes, data *data1);
char	*find_path(char *cmd, char **envp);
char	*path_is_ok(char **paths, char *cmd);
void	process(char **argv, char **envp, data *data1);


#endif
