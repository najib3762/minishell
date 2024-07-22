#include "../minishell"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	p = (char *)malloc(len + 1);
	if (!p)
		return (NULL);
	ft_strlcpy(p, s1, len + 1);
	ft_strlcat(p, s2, len + 1);
	return (p);
}
