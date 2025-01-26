/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_without_pipe.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:03:43 by iriadyns          #+#    #+#             */
/*   Updated: 2025/01/26 16:40:06 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**environ;

void	handle_child_process(t_command *commands, char *path, char *args[])
{
	if (process_redirections(commands) == ERROR)
	{
		ft_putstr_fd("Error: Redirection failed.\n", 2);
		exit(1);
	}
	if (!path)
	{
	}
	if (execve(path, args, environ) == -1)
	{
		exit(126);
	}
}

void	execute_command(t_command *commands, char *path, char *args[])
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("Error: Fork failed.\n", 2);
		return ;
	}
	else if (pid == 0)
		handle_child_process(commands, path, args);
	else
		waitpid(pid, &status, 0);
}

void	execution_without_pipe(t_command *commands)
{
	char	*path;
	char	*args[4];
	int		i = 0;

	if (!commands || !commands->command)
	{
		ft_putstr_fd("Error: Invalid command structure.\n", 2);
		return ;
	}
	if (is_builtin(commands->command))
	{
		execute_builtin(commands);
		return ;
	}
	path = true_path(commands->command, environ);
	args[i++] = commands->command;
	if (commands->options)
		args[i++] = commands->options;
	if (commands->pattern)
		args[i++] = commands->pattern;
	args[i] = NULL;
	execute_command(commands, path, args);
}
