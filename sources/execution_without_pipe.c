/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_without_pipe.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:03:43 by iriadyns          #+#    #+#             */
/*   Updated: 2025/02/17 14:16:19 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**environ;

/**
 * @brief Handles execution in a child process for an external command.
 * Sets up redirections (and here-document if necessary), then attempts to
 * execute the command using execve().
 *
 * @param commands The command structure.
 *
 * @param path The path to the executable.
 *
 * @param args The argument vector for execve.
 */
void	handle_child_process(t_command *commands, char *path, char *args[])
{
	int	pipefd[2];

	if (process_redirections(commands) == ERROR)
		exit(1);
	if (commands->in_type == HERE_DOC && commands->input)
	{
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			exit(1);
		}
		write(pipefd[1], commands->input, ft_strlen(commands->input));
		close(pipefd[1]);
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			close(pipefd[0]);
			exit(1);
		}
		close(pipefd[0]);
	}
	if (!path)
		exit(127);
	if (execve(path, args, environ) == -1)
		exit(126);
}

/**
 * @brief Executes an external command by forking a child process.
 * Forks a new process and in the child calls handle_child_process().
 * The parent waits
 * for the child to finish and updates g_exit_status.
 *
 * @param commands The command structure.
 *
 * @param path The path to the executable.
 *
 * @param args The argument vector for execve.
 */
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
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
	}
}

/**
 * @brief Restores the original file descriptors for standard input and output.
 *
 * @param in The original stdin file descriptor.
 *
 * @param out The original stdout file descriptor.
 */
void	restore_fds(int in, int out)
{
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	close(in);
	close(out);
}

/**
 * @brief Executes a built-in command without piping.
 * Sets up redirections, calls execute_builtin(),
 * and then restores the file descriptors.
 *
 * @param commands The command structure.
 *
 * @return The exit status of the built-in command.
 */
int	exec_builtin_no_pipe(t_command *commands)
{
	int	backup_in;
	int	backup_out;
	int	ret;

	backup_in = dup(STDIN_FILENO);
	backup_out = dup(STDOUT_FILENO);
	if (process_redirections(commands) == ERROR)
	{
		restore_fds(backup_in, backup_out);
		return (SHELL_CONTINUE);
	}
	ret = execute_builtin(&commands);
	restore_fds(backup_in, backup_out);
	return (ret);
}

/**
 * @brief Executes an external command without piping.
 * Constructs the argument vector using build_execve_args(),
 * forks a child process,
 * and executes the command using execve().
 *
 * @param commands The command structure.
 *
 * @return SHELL_CONTINUE on success.
 */
int	exec_external_no_pipe(t_command *commands)
{
	char	**args;
	char	*path;

	path = true_path(commands->command, environ);
	if (!path)
	{
		return (SHELL_CONTINUE);
	}
	args = build_execve_args(commands);
	if (!args)
	{
		free(path);
		return (SHELL_CONTINUE);
	}
	execute_command(commands, path, args);
	free(path);
	free_2d_array(args);
	return (SHELL_CONTINUE);
}
