/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_without_pipe.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:03:43 by iriadyns          #+#    #+#             */
/*   Updated: 2025/01/27 15:49:06 by iriadyns         ###   ########.fr       */
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

static void	restore_fds(int in, int out)
{
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	close(in);
	close(out);
}

void	execution_without_pipe(t_command *commands)
{
	char	*path;
	char	*args[4];
	int		i;
	int		backup_in;
	int		backup_out;

	i = 0;
	if (!commands || !commands->command)
	{
		ft_putstr_fd("Error: Invalid command structure.\n", 2);
		return ;
	}
	if (is_builtin(commands->command))
	{
		backup_in = dup(STDIN_FILENO);
		backup_out = dup(STDOUT_FILENO);
		if (process_redirections(commands) == ERROR)
		{
			restore_fds(backup_in, backup_out);
			return ;
		}
		execute_builtin(commands);
		restore_fds(backup_in, backup_out);
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
