/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_with_pipe_3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:59:28 by iriadyns          #+#    #+#             */
/*   Updated: 2025/02/05 17:03:05 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**environ;

static int	setup_pipe_if_needed(t_command *current, int pipe_fd[2])
{
	if (current->next)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			return (FAIL);
		}
	}
	return (SUCCESS);
}

static void	child_branch(t_command *current, int *pipe_in, int pipe_fd[2],
							char *path)
{
	if (current->next)
		handle_child(current, *pipe_in, pipe_fd, path);
	else
	{
		if (*pipe_in != STDIN_FILENO)
		{
			if (dup2(*pipe_in, STDIN_FILENO) == -1)
			{
				perror("dup2");
				exit(1);
			}
			close(*pipe_in);
		}
		execute_command_pipe(current, path);
		exit(g_exit_status);
	}
}

static void	parent_branch(t_command *current, int *pipe_in, int pipe_fd[2])
{
	if (current->next)
		handle_parent(pipe_fd, pipe_in);
}

int	process_single_command(t_command *current, int *pipe_in)
{
	char	*path;
	int		pipe_fd[2];
	pid_t	pid;

	path = true_path(current->command, environ);
	if (current->next && setup_pipe_if_needed(current, pipe_fd) == FAIL)
		return (free(path), FAIL);
	pid = fork();
	if (pid < 0)
	{
		if (current->next)
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
		}
		return (free(path), FAIL);
	}
	else if (pid == 0)
		child_branch(current, pipe_in, pipe_fd, path);
	else
	{
		parent_branch(current, pipe_in, pipe_fd);
		free(path);
	}
	return (SUCCESS);
}
