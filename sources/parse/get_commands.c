/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_parsing.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmattos <nmattos@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/25 15:40:45 by nmattos       #+#    #+#                 */
/*   Updated: 2025/02/25 15:50:30 by nmattos       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	create_command(t_command **commands, t_token **tokens);
static int	fill_command(t_command **cmd, t_token **tokens);

t_command	*get_commands(t_token *tokens)
{
	t_command	*commands;
	t_token		*current;

	commands = NULL;
	current = tokens;
	while (current != NULL)
	{
		if (create_command(&commands, &current) == FAIL)
		{
			clean_commands(&commands);
			return (NULL);
		}
	}
	return (commands);
}

static int	create_command(t_command **commands, t_token **tokens)
{
	t_command	*cmd;

	cmd = cmd_new(NULL, NULL);
	if (cmd == NULL)
		return (FAIL);
	if (fill_command(&cmd, tokens) == FAIL)
	{
		clean_commands(commands);
		return (FAIL);
	}
	cmd_add_back(commands, cmd);
	return (SUCCESS);
}

static int	fill_command(t_command **cmd, t_token **tokens)
{
	size_t	assignments;

	assignments = 0;
	while ((*tokens) != NULL)
	{
		if ((*tokens)->type == E_PIPE)
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
			if (assign_token(cmd, tokens) == FAIL)
				return (FAIL);
		}
		*tokens = (*tokens)->next;
		assignments++;
	}
	return (SUCCESS);
}
