/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_with_pipe_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:03:19 by iriadyns          #+#    #+#             */
/*   Updated: 2025/02/17 14:21:59 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**environ;

/**
 * @brief Constructs the argument vector for execve from the command structure.
 * This function splits the options and pattern strings by spaces,
 * counts the total number of tokens, allocates an array of strings,
 * and concatenates them with the command name as the first argument.
 *
 * @param current The current command structure.
 *
 * @return A NULL-terminated array of strings (argv) for execve.
 */
char	**get_command_args(t_command *current)
{
	char	**args;
	int		i;

	i = 0;
	args = malloc(sizeof(char *) * 4);
	if (!args)
		return (NULL);
	args[i++] = ft_strdup(current->command);
	if (current->options && ft_strlen(current->options) > 0)
		args[i++] = ft_strdup(current->options);
	if (current->pattern && ft_strlen(current->pattern) > 0)
		args[i++] = ft_strdup(current->pattern);
	args[i] = NULL;
	return (args);
}

/**
 * @brief Sets up input and output redirections for a command in a pipeline.
 * Duplicates file descriptors as necessary.
 *
 * @param current The current command structure.
 *
 * @param pipe_in The input file descriptor.
 *
 * @param pipe_fd The file descriptors for the current pipe.
 */
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

/**
 * @brief Creates a child process for a piped command.
 * Forks a new process; in the child, it executes the command; in the parent,
 * it updates the pipe input.
 *
 * @param current The current command structure.
 *
 * @param pipe_in The current input file descriptor.
 *
 * @param pipe_fd The file descriptors for the pipe.
 *
 * @param path The path to the executable.
 *
 * @return SUCCESS on success, ERROR on failure.
 */
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

/**
 * @brief Waits for all child processes to finish.
 */
void	wait_for_children(void)
{
	while (wait(NULL) > 0)
		;
}
