/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_with_pipe_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:13:56 by iriadyns          #+#    #+#             */
/*   Updated: 2025/03/11 14:45:06 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern char	**environ;

/**
 * @brief Handles execution of a piped child process.
 * Sets up input/output redirections and executes
 * the command in the child process.
 *
 * @param current The current command structure.
 *
 * @param pipe_in The file descriptor to use for input.
 *
 * @param pipe_fd An array of two file descriptors for the current pipe.
 *
 * @param path The path to the executable.
 */
void	handle_child(t_command *current, t_exec_data *exec_data)
{
	setup_input_output(current, exec_data->pipe_in, exec_data->pipe_fd);
	execute_command_pipe(current, exec_data->path, exec_data->shell);
}

/**
 * @brief Handles the parent branch of a piped command.
 * Closes the write end of the pipe and updates the input file descriptor for
 * subsequent commands in the pipeline.
 *
 * @param pipe_fd The array of two file descriptors for the pipe.
 *
 * @param pipe_in Pointer to the input file descriptor to update.
 */
void	handle_parent(int *pipe_fd, int *pipe_in)
{
	close(pipe_fd[1]);
	if (*pipe_in != STDIN_FILENO)
		close(*pipe_in);
	*pipe_in = pipe_fd[0];
}

/**
 * @brief Executes a sequence of piped commands.
 * Iterates through the linked list of commands, processing each command in the
 * pipeline. After forking child processes for each command, waits for all
 * child processes to finish.
 *
 * @param commands The linked list of commands to execute.
 *
 * @return SHELL_CONTINUE upon successful execution.
 */
int	execution_with_pipe(t_command *commands, t_shell *shell)
{
	int			pipe_in;
	t_command	*current;

	pipe_in = STDIN_FILENO;
	current = commands;
	while (current)
	{
		if (process_single_command(current, &pipe_in, shell) == FAIL)
			return (SHELL_CONTINUE);
		current = current->next;
	}
	if (pipe_in != STDIN_FILENO)
		close(pipe_in);
	wait_for_children();
	return (SHELL_CONTINUE);
}

/**
 * @brief Creates a new pipe.
 * Attempts to create a pipe and prints the file descriptors on success.
 *
 * @param pipe_fd Pointer to an array of two integers where the pipe's file
 * descriptors will be stored.
 *
 * @return SUCCESS if the pipe was created successfully, ERROR otherwise.
 */
int	setup_pipe(int *pipe_fd)
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (ERROR);
	}
	printf("Pipe created: read_fd=%d, write_fd=%d\n", pipe_fd[0], pipe_fd[1]);
	return (SUCCESS);
}
