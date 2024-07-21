#include"../minishell.h"

t_list	*m_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	addback_node_free(&g_global->address, newnode_free(node));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

static int	len(int *nb)
{
	long	m;
	int		count;

	m = *nb;
	count = 0;
	if (m < 0 || m == 0)
	{
		m = -(m);
		count += 1;
	}
	while (m != 0)
	{
		m /= 10;
		count++;
	}
	return (count);
}

char	*m_itoa(int n)
{
	long	x;
	long	l;
	char	*p;

	l = len(&n);
	x = n;
	p = (char *)malloc(l + 1);
	addback_node_free(&g_global->address, newnode_free(p));
	if (!p)
		return (0);
	if (x < 0)
	{
		x *= -1;
		p[0] = '-';
	}
	if (n == 0)
		p[0] = '0';
	p[l] = '\0';
	while (x > 0)
	{
		p[l - 1] = (x % 10) + '0';
		x /= 10;
		l--;
	}
	return (p);
}

char	*m_strjoin(char const *s1, char const *s2)
{
	char	*p;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	p = (char *)malloc(len + 1);
	addback_node_free(&g_global->address, newnode_free(p));
	if (!p)
		return (NULL);
	ft_strlcpy(p, s1, len + 1);
	ft_strlcat(p, s2, len + 1);
	return (p);
}

char	*m_strdup(const char *s)
{
	char	*p;
	size_t	i;

	i = 0;
	p = (char *)malloc(sizeof(char) * ((ft_strlen(s)) + 1));
	addback_node_free(&g_global->address, newnode_free(p));
	if (!p)
		return (0);
	while (*s)
		p[i++] = *s++;
	p[i] = '\0';
	return (p);
}

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
