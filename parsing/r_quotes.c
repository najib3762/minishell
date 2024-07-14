#include "../minishell.h"

void	r_quotes(t_token **head)
{
	t_token *temp = *head;

	while (temp)
	{
		if (temp->type == TOKEN_WORD)
		{
			if (check_qoutes(temp->value))
				temp->value = skip_quotes(temp->value);
		}
		temp = temp->next;
	}
}