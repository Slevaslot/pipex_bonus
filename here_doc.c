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

int	here_doc_01(char *limit, data *data)
{
	char	*buffer;
	buffer = malloc(sizeof(char ) * 5000);
	pipe(data->here_doc);
	limit = ft_strjoin(limit, "\n");
	if (!limit)
		return(free(limit), 0);
	buffer = lire_entree();
	ft_putstr_fd(buffer, data->here_doc[1]);
	return (0);
}

int	here_doc(char *limiter, data *data)
{
	char	*buffer;
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	pipe(data->here_doc);
	limiter = ft_strjoin(limiter, "\n");
	if (!limiter)
		return(free(limiter), 0);
	buffer = get_next_line(0);
	while (buffer[i])
	{
		if (buffer[i] == limiter[j])
		{
			while(buffer[i] == limiter[j])
			{
				i++;
				j++;
			}
			if (j == ft_strlen(limiter))
				return (0);
			i = i - j;
			j = 0;
		}
		write (data->here_doc[1], &buffer[i], 1);
		i++;
	}
	// while((buffer = get_next_line(0)))
	// {
	// 	ft_putstr_fd(buffer,data->here_doc[1]);
	// 	if(buffer[i] == limiter[j])
	// 	{
	// 		while(buffer[i] == limiter[j])
	// 		{
	// 			i++;
	// 			j++;
	// 		}
	// 		if (j == ft_strlen(limiter))
	// 			break ;
	// 		else
	// 		{
	// 			j = 0;
	// 			i = 0;
	// 		}

	// 	}
	// }
	return(0);
}
