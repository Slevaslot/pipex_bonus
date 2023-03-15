#include "pipex.h"

void	ft_freetab(char **str)
{
	int i = 0;

	while(str[i])
	{
		free(str[i]);
		i++;
	}
}

void	ft_putstr_fd_for_here(char *s, char *limiter, int fd)
{
	size_t	i;
	size_t	j;
	if (!s)
		return ;
	j = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == limiter[j])
		{
			while(s[i] == limiter[j])
			{
				i++;
				j++;
			}
			if (j == ft_strlen(limiter))
				break;
			i = i - j;
			j = 0;
		}
		write (fd, &s[i], 1);
		i++;
	}
}

char* lire_entree() {
    int taille_max = 100; // Taille maximale de la chaîne de caractères
    char* chaine = (char*) malloc(sizeof(char) * taille_max);
    int index = 0;
    char c;

    while ((c = getchar()) != 'd') { // Tant que l'utilisateur n'appuie pas sur la touche Entrée
        if (index == taille_max - 1) { // Si la chaîne de caractères est pleine
            taille_max *= 2;
            chaine = (char*) realloc(chaine, sizeof(char) * taille_max);
        }
        chaine[index++] = c; // Ajout du caractère dans la chaîne
    }

    chaine[index] = '\0'; // Ajout du caractère de fin de chaîne

    return chaine;
}

void	here_doc_02(char *argv, data *data)
{
	int		file;
	char	*buf;
	// (void)argv;
	file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 777);
	if (file < 0)
		ft_putstr_fd("ERR_HEREDOC", 2);
	while (1)
	{
		write(1, "heredoc> ", 9);
		buf = get_next_line(0);
		if (!buf)
			break ;
		if (!ft_strncmp(argv, buf, ft_strlen(argv)))
			break ;
		ft_putstr_fd(buf, file);
		// write(file, "\n", 1);
		free(buf);
	}
	free(buf);
	close(file);
	data->fd_in = open(".heredoc_tmp", O_RDONLY);
	if (data->fd_in < 0)
	{
		error();
		ft_putstr_fd("ERR_HEREDOC", 2);
	}
}

void	here_doc(char *argv, data *data)
{
	char	*buf;
	pipe(data->here_doc);
	while (1)
	{
		write(1, "heredoc> ", 9);
		buf = get_next_line(0);
		if (!buf)
			break ;
		if (!ft_strncmp(argv, buf, ft_strlen(argv)))
			break ;
		ft_putstr_fd(buf, data->here_doc[1]);
		// write(file, "\n", 1);
		free(buf);
	}
	free(buf);
	close(data->here_doc[1]);
	data->fd_in = data->here_doc[0];
	if (data->fd_in < 0)
	{
		error();
		ft_putstr_fd("ERR_HEREDOC", 2);
	}
}

