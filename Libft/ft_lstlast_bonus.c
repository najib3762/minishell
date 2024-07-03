/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:11:20 by mlamrani          #+#    #+#             */
/*   Updated: 2023/12/05 18:45:43 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*node;

	node = lst;
	if (!lst)
		return (NULL);
	while (node->next)
		node = node->next;
	return (node);
}

// int main(){
//     t_list *first = ft_lstnew("banana");
//     t_list *second = ft_lstnew("apple");
//     t_list *third = ft_lstnew("fruit");
//     first->next = second;
//     second->next = third;
//     third->next = NULL;

//     t_list *lastone = ft_lstlast(first);
//     printf("%s\n",(char *)lastone->content);

//     while(first)
//     {
//         t_list *t = first->next;
//         free(first);
//         first = t;
//     }
// }