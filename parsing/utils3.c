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


