#include "include/minishell.h"
#include "include/libft.h"


void	lstdelone(t_token *head, void (*del)(void *))
{
	if (head != NULL)
	{
		(*del)(head->value);
		free(head);
	}
}