/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_with_pipe_3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:59:28 by iriadyns          #+#    #+#             */
/*   Updated: 2025/02/28 14:42:00 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern char	**environ;

/**
 * @brief Sets up a new pipe if there is a subsequent command.
 * Checks whether the current command has a next command, and if so, creates a
 * new pipe for inter-process communication.
 *
 * @param current The current command structure.
 *
 * @param pipe_fd An array of two integers to store
 * the new pipe's file descriptors.
 *
 * @return SUCCESS if no next command exists or if the pipe was
 * created successfully, FAIL otherwise.
 */
int	setup_pipe_if_needed(t_command *current, int pipe_fd[2])
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
void	child_branch(t_child_data *child)
{
	if (child->current->next)
	{
		setup_input_output(child->current, *(child->pipe_in), child->pipe_fd);
		execute_command_pipe(child->current, child->path, child->shell);
	}
	else
	{
		if (*(child->pipe_in) != STDIN_FILENO)
		{
			if (dup2(*(child->pipe_in), STDIN_FILENO) == -1)
			{
				perror("dup2");
				exit(1);
			}
			close(*(child->pipe_in));
		}
		execute_command_pipe(child->current, child->path, child->shell);
		exit(child->shell->exit_status);
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
void	parent_branch(t_command *current, int *pipe_in, int pipe_fd[2])
{
	if (current->next)
		handle_parent(pipe_fd, pipe_in);
}
