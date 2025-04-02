/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:10:45 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/02 16:15:15 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern char	**environ;

static int	validate_and_fix_command(t_command *cmd, t_shell *shell)
{
	if (!cmd->command || cmd->command[0] == '\0')
	{
		if (cmd->redirect)
		{
			cmd->command = ft_strdup("cat");
			if (!cmd->command)
			{
				ft_putstr_fd("minishell: allocation error\n", 2);
				shell->exit_status = 2;
				return (2);
			}
		}
		else
		{
			ft_putstr_fd("minishell: syntax error near"
				"unexpected token `newline'\n", 2);
			shell->exit_status = 2;
			return (2);
		}
	}
	return (0);
}

int	check_commands_for_pipe(t_command *commands, t_shell *shell)
{
	t_command	*current;
	int			is_pipe;
	int			ret;

	is_pipe = 0;
	current = commands;
	while (current)
	{
		ret = validate_and_fix_command(current, shell);
		if (ret != 0)
			return (ret);
		if (current->next != NULL)
		{
			is_pipe = 1;
			break ;
		}
		current = current->next;
	}
	return (is_pipe);
}
