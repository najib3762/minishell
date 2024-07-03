/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:54:29 by mlamrani          #+#    #+#             */
/*   Updated: 2023/12/05 18:46:00 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new || !lst)
		return ;
	new->next = *lst;
	*lst = new;
}

// int main()
// {
//     t_list *x = ft_lstnew("world");
//     t_list *new_x = ft_lstnew("hello");
//     ft_lstadd_front(&x, new_x);
//     while(x)
//     {
//         printf("the content : %s\n", (char *)x->content);
//         x = x->next;
//     }
//     while(x)
//     {
//         t_list *t = x->next;
//         free(x);
//         x = t;
//     }
// }