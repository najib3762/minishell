#include"../minishell.h"




size_t	count_strings(char *s, char c1, char c2)
{
	size_t	nb_strings;


     if(!s)
		return (0);
	nb_strings = 0;
	while (*s != '\0')
	{
		if (*s != c1 && *s != c2)
		{
			while (*s != '\0' && (*s != c1 &&*s != c2))
				s++;
			nb_strings++;
			continue ;
		}
		s++;
	}
	return (nb_strings);
}


char	*dup_word(char **dest, char *src, char c1, char c2)
{
	size_t	len;
	size_t	i;

	while (*src == c1 || *src == c2)
		src++;
	len = 0;
	while (src[len] != '\0' && (src[len] != c1 && src[len] != c2))
		len++;
	*dest = (char *)malloc(sizeof(char) * (len + 1));
	if (*dest == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		(*dest)[i] = src[i];
		i++;
	}
	(*dest)[i] = '\0';
	src += len + 1;
	return (src);
}

void	free_strs(char ***strs, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		free((*strs)[i]);
		i++;
	}
	free(*strs);
	*strs = NULL;
}

char	**m_split(char *s, char c1, char c2)
{
	char	**strs;
	size_t	nbr_strings;
	size_t	i;
    

	nbr_strings = count_strings(s, c1, c2);
	strs = (char **)malloc(sizeof(char *) * (nbr_strings + 1));
	if (strs != NULL)
	{
		strs[nbr_strings] = NULL;
		i = 0;
		while (i < nbr_strings)
		{
			s = dup_word(strs + i, s, c1, c2);
			if (s == NULL)
			{
				free_strs(&strs, i);
				break ;
			}
			i++;
		}
	}
	return (strs);
}
