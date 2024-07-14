#include "../minishell.h"

char	*dollar_here_doc(char *line, int *i, t_mini *prog)
{
	char	*var_name;
	char	*var_value;

	var_name = NULL;
	var_value = NULL;
	(*i)++;
	while (ft_isalpha(line[*i]) || ft_isdigit(line[*i]) || line[*i] == '_')
	{
		var_name = ft_strjoin_char(var_name, line[*i]);
		(*i)++;
	}
	var_value = get_env_value(var_name, prog->env_head);
	if (var_value)
		return (free(var_name), var_value);
	return (free(var_name), NULL);
}

char	*ft_expand(char *line, t_mini *prog)
{
	char	*new_line;
	int		i;

	new_line = NULL;
	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && (ft_isdigit(line[i + 1])) && line[i + 2] != '\0')
			i += 2;
		if (line[i] == '$' && (ft_isalpha(line[i + 1]) || \
		ft_isdigit(line[i + 1])))
			new_line = my_strjoin(new_line, dollar_here_doc(line, &i, prog));
		else
		{
			new_line = my_strjoin(new_line, ft_strdup_char(line[i]));
			i++;
		}
	}
	return (new_line);
}