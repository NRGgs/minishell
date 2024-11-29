/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:00:09 by nmattos-          #+#    #+#             */
/*   Updated: 2024/10/10 16:24:28 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static t_list	*init_new_node(t_list *node_src, t_list *head,
								void *(*f)(void *), void (*del)(void *))
{
	void	*new_content;
	t_list	*node_dest;

	new_content = f(node_src->content);
	node_dest = ft_lstnew(new_content);
	if (node_dest == NULL)
	{
		ft_lstclear(&head, del);
		return (NULL);
	}
	return (node_dest);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*node_src;
	t_list	*node_dest;

	node_src = lst;
	head = NULL;
	node_dest = init_new_node(node_src, head, f, del);
	if (node_dest == NULL)
		return (NULL);
	head = node_dest;
	node_src = node_src->next;
	while (node_src != NULL)
	{
		node_dest = init_new_node(node_src, head, f, del);
		if (node_dest == NULL)
			return (NULL);
		ft_lstadd_back(&head, node_dest);
		node_src = node_src->next;
	}
	return (head);
}
