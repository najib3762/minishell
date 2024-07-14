#include "../minishell.h"

#define FILENAME "/tmp/here_doc_"

char	*random_file(void)
{
	char		*filename;
	static int	i;
	char		*temp;

	temp = NULL;
	temp = ft_itoa(i++);
	filename = ft_strjoin(FILENAME, temp);
	if (!filename)
	{
		perror("malloc");
		return (NULL);
	}
	return (free(temp), filename);
}

void	change_value(t_token *token, char *filename)
{
	token->value = "<";
	token->type = TOKEN_IN;
	token->next->value = filename;
	token->next->type = TOKEN_WORD;
}

int	calcule_qoutes(char *str)
{
	int	dflag;
	int	sflag;
	int	res;
	int	i;

	dflag = 0;
	sflag = 0;
	res = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' && sflag == 0)
		{
			res += 1;
			dflag = !dflag;
		}
		if (str[i] == '\'' && dflag == 0)
		{
			res += 1;
			sflag = !sflag;
		}
		i++;
	}
	return (res);
}

void	g_word(char *str, char *eof)
{
	int	dflag;
	int	sflag;
	int	i;
	int	j;

	dflag = 0;
	sflag = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\"' && sflag == 0 && ++i)
			dflag = !dflag;
		else if (str[i] == '\'' && dflag == 0 && ++i)
			sflag = !sflag;
		else
			eof[j++] = str[i++];
	}
	eof[j] = '\0';
}

char	*skip_quotes(char *str)
{
	char	*eof;
	int		len;
	int		qoutes;

	qoutes = calcule_qoutes(str);
	len = ft_strlen(str) - qoutes;
	eof = malloc(sizeof(char) * (len + 1));
	if (!eof)
	{
		perror("malloc");
		exit(1);
	}
	g_word(str, eof);
	return (eof);
}