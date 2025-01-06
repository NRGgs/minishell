/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:06:48 by iriadyns          #+#    #+#             */
/*   Updated: 2025/01/06 09:48:04 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**environ;

void	execute_commands(t_command *commands)
{
	t_command	*current;
	int			is_pipe;

	if (!commands)
	{
		ft_putstr_fd("Error: Command structure is NULL.\n", 2);
		return ;
	}
	current = commands;
	is_pipe = 0;
	while (current)
	{
		if (current->out_type == PIPE || current->in_type == PIPE)
		{
			is_pipe = 1;
			break ;
		}
		current = current->next;
	}
	if (is_pipe)
		execution_with_pipe(commands);
	else
		execution_without_pipe(commands);
}
