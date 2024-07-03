/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 04:15:43 by mlamrani          #+#    #+#             */
/*   Updated: 2023/12/05 18:45:56 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*next;

	if (!lst || !del)
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		(*del)(current->content);
		free(current);
		current = next;
	}
	*lst = NULL;
}
// void delete(void *content)
// {
//     free(content);
// }
// int main(){
//     t_list *a = ft_lstnew("hello");
//     t_list  *b = ft_lstnew("world");
//     printf ("the content of a : %s\n", (char *)a->content);
//     printf ("the content of b : %s\n", (char *)b->content);
//     a->next = b;
//     b->next = NULL;
//     ft_lstclear(&a, &delete);
//     if(a == NULL)
//         printf("the list is empty\n");
//     else
//         printf("the list isn't empty\n");
// }