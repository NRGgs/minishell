/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:06:48 by iriadyns          #+#    #+#             */
/*   Updated: 2024/12/10 12:06:38 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../includes/execution.h"
#include "../../includes/minishell.h"

extern char **environ;

void execute_commands(t_command *commands)
{
	t_command *current;
	int is_pipe;

	if (!commands)
	{
		ft_putstr_fd("Error: Command structure is NULL.\n", 2);
		return;
	}

	current = commands;
	is_pipe = 0;
	while (current)
	{
		if (current->out_type == PIPE || current->in_type == PIPE)
		{
			is_pipe = 1;
			break;
		}
		current = current->next;
	}

	if (is_pipe)
		execution_with_pipe(commands);
	else
		execution_without_pipe(commands);
}

void execution_without_pipe(t_command *commands)
{
	pid_t pid;
	int status;

	if (!commands || !commands->command)
	{
		ft_putstr_fd("Error: Invalid command structure.\n", 2);
		return;
	}

	if (is_builtin(commands->command))
	{
		if (execute_builtin(commands) == 1)
		{
			ft_putstr_fd("Error: Built-in command execution failed.\n", 2);
		}
		return;
	}

	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("Error: Fork failed.\n", 2);
		return;
	}
	else if (pid == 0)
	{
		char *path = true_path(commands->command, environ);
		if (!path)
		{
			ft_putstr_fd("Error: Command not found.\n", 2);
			exit(127);
		}
		char *args[] = {commands->command, commands->input, NULL};

		if (execve(path, args, environ) == -1)
		{
			ft_putstr_fd("Error: Execve failed.\n", 2);
			exit(126);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

void execution_with_pipe(t_command *commands)
{
	int pipe_fd[2];
	pid_t pid;
	t_command *current;
	int pipe_in = STDIN_FILENO;
	int pipe_out = STDOUT_FILENO;
	int status;

	current = commands;
	while (current)
	{
		if (current->next)
		{
			if (pipe(pipe_fd) == -1)
			{
				ft_putstr_fd("Error: Pipe failed.\n", 2);
				return;
			}
			pipe_out = pipe_fd[1];
		}
		else
			pipe_out = STDOUT_FILENO;

		pid = fork();
		if (pid < 0)
		{
			ft_putstr_fd("Error: Fork failed.\n", 2);
			return;
		}
		else if (pid == 0)
		{
			if (pipe_in != STDIN_FILENO)
				dup2(pipe_in, STDIN_FILENO);
			if (pipe_out != STDOUT_FILENO)
				dup2(pipe_out, STDOUT_FILENO);
			close(pipe_fd[0]);
			close(pipe_fd[1]);

			if (is_builtin(current->command))
			{
				if (execute_builtin(current) == 1)
				{
					ft_putstr_fd("Error: Built-in command execution failed.\n", 2);
					exit(1);
				}
				exit(0);
			}

			char *path = true_path(current->command, environ);
			if (!path)
			{
				ft_putstr_fd("Error: Command not found.\n", 2);
				exit(127);
			}
			char *args[] = {current->command, current->input, current->options, NULL};

			if (execve(path, args, environ) == -1)
			{
				ft_putstr_fd("Error: Execve failed.\n", 2);
				exit(126);
			}
		}
		else
		{
			close(pipe_fd[1]);
			pipe_in = pipe_fd[0];
		}

		current = current->next;
	}
	while (wait(&status) > 0)
		;
}
