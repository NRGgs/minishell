/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_without_pipe.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:03:43 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/09 14:16:51 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern char	**environ;

/**
 * @brief Executes an external command by forking a child process.
 * Forks a new process and in the child calls handle_child_process().
 * The parent waits
 * for the child to finish and updates exit_status.
 *
 * @param commands The command structure.
 *
 * @param path The path to the executable.
 *
 * @param args The argument vector for execve.
 */
void	execute_command(t_command *commands, char *path,
			char *args[], t_shell *shell)
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
	{
		signal(SIGINT, command_handler);
		signal(SIGQUIT, command_handler);
		handle_child_process(commands, path, args, shell);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
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
int	exec_builtin_no_pipe(t_command *commands, t_shell *shell)
{
	int	backup_in;
	int	backup_out;
	int	ret;

	backup_in = dup(STDIN_FILENO);
	backup_out = dup(STDOUT_FILENO);
	if (process_redirections(commands, shell) == ERROR)
	{
		restore_fds(backup_in, backup_out);
		return (SHELL_CONTINUE);
	}
	ret = execute_builtin(&commands, shell);
	restore_fds(backup_in, backup_out);
	return (ret);
}
