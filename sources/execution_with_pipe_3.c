/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_with_pipe_3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:59:28 by iriadyns          #+#    #+#             */
/*   Updated: 2025/02/17 15:07:19 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**environ;

/**
 * @brief Sets up a new pipe if there is a subsequent command.
 * Checks whether the current command has a next command, and if so, creates a
 * new pipe for inter-process communication.
 *
 * @param current The current command structure.
 *
 * @param pipe_fd An array of two integers to store the new pipe's file descriptors.
 *
 * @return SUCCESS if no next command exists or if the pipe was
 * created successfully, FAIL otherwise.
 */
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

/**
 * @brief Handles the child branch of a piped command.
 * Sets up redirections and executes the command.
 *
 * @param current The current command structure.
 *
 * @param pipe_in Pointer to the current input file descriptor.
 *
 * @param pipe_fd The file descriptors for the pipe.
 *
 * @param path The path to the executable.
 */
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

/**
 * @brief Handles the parent branch after forking a piped command.
 * Closes the write end of the pipe and updates the input for the next command.
 *
 * @param current The current command structure.
 *
 * @param pipe_in Pointer to the current input file descriptor.
 *
 * @param pipe_fd The file descriptors for the pipe.
 */
static void	parent_branch(t_command *current, int *pipe_in, int pipe_fd[2])
{
	if (current->next)
		handle_parent(pipe_fd, pipe_in);
}

/**
 * @brief Processes a single command in a pipeline.
 * Determines the executable path, forks a child process to execute it,
 * and frees resources.
 *
 * @param current The current command structure.
 *
 * @param pipe_in Pointer to the input file descriptor.
 *
 * @return SUCCESS on success, FAIL on failure.
 */
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
