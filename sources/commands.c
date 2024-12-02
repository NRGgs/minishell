/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:47:18 by nmattos-          #+#    #+#             */
/*   Updated: 2024/12/02 16:53:36 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"

/*	Create a new command.
 *
 *	command:	the name of the command.
 *	options:	the options of the command.
 *
 *	Return: the new command.
 */
t_command	*cmd_new(char *command, char *options)
{
	t_command	*new_cmd;

	new_cmd = malloc(sizeof(t_command));
	if (new_cmd == NULL)
		return (NULL);
	new_cmd->command = ft_strdup(command);
	if (new_cmd->command == NULL)
	{
		free(new_cmd);
		return (NULL);
	}
	new_cmd->options = ft_strdup(options);
	{
		free(new_cmd->command);
		free(new_cmd);
		return (NULL);
	}
	new_cmd->in_type = 0;
	new_cmd->out_type = 0;
	new_cmd->input = NULL;
	new_cmd->output = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

/*	Return the last command in the linked list.
 *
 *	cmds:	the linked list of commands.
 *
 *	Return: the last command.
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

/*	Add a new command to the end of the linked list.
 *
 *	cmds:		the start of the linked list.
 *	new_cmd:	the new command.
 *
 * 	Return: void.
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
