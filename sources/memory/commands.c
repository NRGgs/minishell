/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:47:18 by nmattos-          #+#    #+#             */
/*   Updated: 2025/02/21 12:44:10 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Initialize the command's variables.
 *
 * @param cmd The command to initialize.
 *
 * @return void.
 */
static void	initialize_command(t_command **cmd)
{
	(*cmd)->in_type = STDIN;
	(*cmd)->out_type = STDOUT;
	(*cmd)->input = NULL;
	(*cmd)->output = NULL;
	(*cmd)->pattern = NULL;
	(*cmd)->next = NULL;
	(*cmd)->env_list = NULL;
}

/**
 * Create a new command.
 *
 * @param command The name of the command.
 * @param options The options of the command.
 *
 * @return The new command.
 */
t_command	*cmd_new(char *command, char *options)
{
	t_command	*new_cmd;

	new_cmd = malloc(sizeof(t_command));
	if (new_cmd == NULL)
		return (NULL);
	if (command == NULL)
		new_cmd->command = NULL;
	else
	{
		new_cmd->command = ft_strdup(command);
		if (new_cmd->command == NULL)
			return (free(new_cmd), NULL);
	}
	if (options == NULL)
		new_cmd->options = NULL;
	else
	{
		new_cmd->options = ft_strdup(options);
		if (new_cmd->options == NULL)
			return (free(new_cmd->command), free(new_cmd), NULL);
	}
	initialize_command(&new_cmd);
	return (new_cmd);
}

/**
 * Return the last command in the linked list.
 *
 * @param cmds the linked list of commands.
 * @return the last command.
 */
t_command	*cmd_last(t_command *cmds)
{
	t_command	*last;

	if (cmds == NULL)
		return (NULL);
	last = cmds;
	while (last->next != NULL)
		last = last->next;
	return (last);
}

/**
 * Add a new command to the end of the linked list.
 *
 * @param cmds     The start of the linked list.
 * @param new_cmd  The new command.
 *
 * @return void
 */
void	cmd_add_back(t_command **cmds, t_command *new_cmd)
{
	t_command	*last;

	if (*cmds == NULL)
		*cmds = new_cmd;
	else
	{
		last = cmd_last(*cmds);
		last->next = new_cmd;
	}
}
