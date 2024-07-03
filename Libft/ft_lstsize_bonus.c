/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:38:39 by mlamrani          #+#    #+#             */
/*   Updated: 2023/12/05 18:45:28 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*p;

	count = 0;
	if (!lst)
		return (count);
	p = lst;
	while (p)
	{
		count++;
		p = p->next;
	}
	return (count);
}
// int main(){
//     t_list *x = ft_lstnew("hello");
//     t_list *m = ft_lstnew("world");
//     x->next = m;
//     m->next = NULL;
//     printf("%d\n",ft_lstsize(x));
//       while (x) {
//         t_list *temp = x->next;
//         free(x);
//         x = temp;
//     }
// }