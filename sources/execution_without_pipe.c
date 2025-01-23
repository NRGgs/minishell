/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_without_pipe.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:03:43 by iriadyns          #+#    #+#             */
/*   Updated: 2025/01/23 12:32:17 by iriadyns         ###   ########.fr       */
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
		// ft_putstr_fd("Error: Command not found.\n", 2);
		// exit(127);
	}
	if (execve(path, args, environ) == -1)
	{
		// ft_putstr_fd("Error: Execve failed.\n", 2);
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
	char	*args[3];

	if (!commands || !commands->command)
	{
		ft_putstr_fd("Error: Invalid command structure.\n", 2);
		return ;
	}
	if (is_builtin(commands->command))
	{
		if (execute_builtin(commands) == 1)
			ft_putstr_fd("Error: Built-in command execution failed.\n", 2);
		return ;
	}
	path = true_path(commands->command, environ);
	args[0] = commands->command;
	args[1] = commands->pattern;
	args[2] = NULL;
	execute_command(commands, path, args);
}
