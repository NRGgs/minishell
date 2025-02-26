/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:40:45 by nmattos           #+#    #+#             */
/*   Updated: 2025/02/26 13:08:28 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	create_command(t_command **commands, \
		t_token **tokens, t_token **current);
static int	fill_command(t_command **cmd, t_token **tokens, t_token **current);

t_command	*get_commands(t_token *tokens)
{
	t_command	*commands;
	t_token		*current;

	commands = NULL;
	current = tokens;
	while (current != NULL)
	{
		if (create_command(&commands, &tokens, &current) == FAIL)
		{
			clean_commands(&commands);
			return (NULL);
		}
	}
	return (commands);
}

static int	create_command(t_command **commands, t_token **tokens, t_token **current)
{
	t_command	*cmd;

	cmd = cmd_new(NULL, NULL);
	if (cmd == NULL)
		return (FAIL);
	if (fill_command(&cmd, tokens, current) == FAIL)
	{
		cmd_clear(&cmd);
		clean_commands(commands);
		return (FAIL);
	}
	cmd_add_back(commands, cmd);
	return (SUCCESS);
}

static int	fill_command(t_command **cmd, t_token **tokens, t_token **current)
{
	size_t	assignments;

	assignments = 0;
	while ((*current) != NULL)
	{
		if ((*current)->type == E_PIPE)
		{
			if (assignments > 0)
			{
				(*cmd)->out_type = PIPE;
				return (SUCCESS);
			}
			(*cmd)->in_type = PIPE;
		}
		else
		{
			if (assign_token(cmd, tokens, current) == FAIL)
				return (FAIL);
		}
		*current = (*current)->next;
		assignments++;
	}
	return (SUCCESS);
}
