/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 18:26:41 by mlamrani          #+#    #+#             */
/*   Updated: 2023/12/05 18:34:01 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
}

// int main(){
//     t_list *a = ft_lstnew("hello");
//     t_list *b = ft_lstnew("mister");
//     a->next = b;
//     b->next = NULL;
//     t_list *c = ft_lstnew("kkklll");
//     ft_lstadd_back(&a, c);
//     t_list *last = a;
//     while (last->next)
//         last = last->next;
//     printf("the content : %s\n", (char *)last->content);

//     while (a){
//         t_list *t = a->next;
//         free(a);
//         a = t;
//     }
// }

// int main()
// {
// 	t_list *node1;
// 	t_list *node2;

// 	int n1 = 7;
// 	int n2 = 4;
// 	int n3 = 9;
// 	node1 = ft_lstnew(&n1);
// 	node2 = ft_lstnew(&n2);
// 	node1->next = node2;
// 	node2->next = NULL;
// 	ft_lstadd_back(&node1, ft_lstnew(&n3));
// 	while(node1)
// 	{
// 		printf("%d -> ",*(int *)node1->content);
// 		node1 = node1->next;
// 	}
// 	return (0);
// }