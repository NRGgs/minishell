/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:59:52 by nmattos-          #+#    #+#             */
/*   Updated: 2024/10/09 17:46:25 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_lstsize(t_list *list)
{
	t_list	*node;
	int		node_count;

	node_count = 0;
	node = list;
	while (node != NULL)
	{
		node_count++;
		node = node->next;
	}
	return (node_count);
}
