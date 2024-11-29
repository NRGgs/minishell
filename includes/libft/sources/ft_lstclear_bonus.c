/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:49:23 by nmattos-          #+#    #+#             */
/*   Updated: 2024/10/09 17:26:16 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;
	t_list	*bin;

	if (del == NULL || *lst == NULL)
		return ;
	node = *lst;
	while (node != NULL)
	{
		bin = node;
		node = node->next;
		del(bin->content);
		free(bin);
	}
	*lst = NULL;
}
