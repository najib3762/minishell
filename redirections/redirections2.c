#include"../minishell.h"

int	close_free(t_fd **head)
{
	t_fd	*temp;

	if (!*head)
		return (0);
	while (*head)
	{
		temp = *head;
		*head = (*head)->next;
		close(temp->fd);
		free(temp);
	}
	return (0);
}

t_fd	*ft_new_fd(int fd)
{
	t_fd	*new_node;

	new_node = (t_fd *)malloc(sizeof(t_fd));
   addback_node_free(&g_global->address, newnode_free(new_node));
	if (!new_node)
		return (NULL);
	new_node->fd = fd;
	new_node->next = NULL;
	return (new_node);
}

void	ft_addback_fd(t_fd **head, t_fd *new_node)
{
	t_fd	*temp;
     if (!*head || !new_node)
		return ;
	if (!*head)
	{
		*head = new_node;
		return ;
	}
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
}
