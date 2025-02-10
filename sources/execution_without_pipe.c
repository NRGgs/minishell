/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_without_pipe.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:03:43 by iriadyns          #+#    #+#             */
/*   Updated: 2025/02/10 18:49:38 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**environ;

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

void	restore_fds(int in, int out)
{
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	close(in);
	close(out);
}

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

int	exec_external_no_pipe(t_command *commands)
{
	char	*args[4];
	char	*path;
	int		i;

	i = 0;
	path = true_path(commands->command, environ);
	if (!path)
	{
		return (SHELL_CONTINUE);
	}
	args[i++] = commands->command;
	if (commands->options)
		args[i++] = commands->options;
	if (commands->pattern)
		args[i++] = commands->pattern;
	args[i] = NULL;
	execute_command(commands, path, args);
	free(path);
	return (SHELL_CONTINUE);
}
