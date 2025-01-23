/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_with_pipe_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:03:19 by iriadyns          #+#    #+#             */
/*   Updated: 2025/01/23 12:33:25 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**environ;

char	**get_command_args(t_command *current)
{
	char	**args;

	if (current->input && ft_strlen(current->input) > 0)
		args = ft_split(current->input, ' ');
	else if (current->pattern)
	{
		args = malloc(sizeof(char *) * 3);
		if (!args)
			return (NULL);
		args[0] = ft_strdup(current->command);
		args[1] = ft_strdup(current->pattern);
		args[2] = NULL;
	}
	else
	{
		args = malloc(sizeof(char *) * 2);
		if (!args)
			return (NULL);
		args[0] = ft_strdup(current->command);
		args[1] = NULL;
	}
	return (args);
}

void	setup_input_output(t_command *current, int pipe_in, int *pipe_fd)
{
	if (pipe_in != STDIN_FILENO)
	{
		if (dup2(pipe_in, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(1);
		}
		close(pipe_in);
	}
	if (current->next)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(1);
		}
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

void	execute_command_pipe(t_command *current, char *path)
{
	char	**args;

	if (process_redirections(current) == ERROR)
	{
		ft_putstr_fd("Error: Redirection failed.\n", 2);
		exit(1);
	}
	if (!path)
		exit(127);
	args = get_command_args(current);
	if (!args || execve(path, args, environ) == -1)
	{
		perror("execve");
		exit(126);
	}
}

int	create_child_process(t_command *current, int pipe_in,
		int *pipe_fd, char *path)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (ERROR);
	}
	else if (pid == 0)
		handle_child(current, pipe_in, pipe_fd, path);
	else
		handle_parent(pipe_fd, &pipe_in);
	return (SUCCESS);
}

void	wait_for_children(void)
{
	while (wait(NULL) > 0)
		;
}
