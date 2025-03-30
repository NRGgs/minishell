/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirects.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmattos <nmattos@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/30 12:27:10 by nmattos       #+#    #+#                 */
/*   Updated: 2025/03/30 13:00:47 by nmattos       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_redirect	*new_redirect(int type, bool is_input, char *arg)
{
	t_redirect	*node;

	node = malloc(sizeof(t_redirect));
	if (!node)
			return (NULL);
	if (arg)
	{
		node->arg = ft_strdup(arg);
		if (!node->arg)
			return (free(node), NULL);
	}
	node->type = type;
	node->is_input = is_input;
	node->next = NULL;
	return (node);
}

t_redirect	*redirect_last(t_redirect *node)
{
	t_redirect	*last;

	if (node == NULL)
		return (NULL);
	last = node;
	while (last->next != NULL)
		last = last->next;
	return (last);
}

void	add_redirect(t_redirect **head, t_redirect *new)
{
	t_redirect	*last;

	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	last = redirect_last(*head);
	last->next = new;
}
