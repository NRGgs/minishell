/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_with_pipe_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:03:19 by iriadyns          #+#    #+#             */
/*   Updated: 2025/02/05 16:53:36 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**environ;

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
	if (is_builtin(current->command))
	{
		execute_builtin(current);
		exit(0);
	}
	else
	{
		if (!path)
			exit(127);
		{
			args = get_command_args(current);
			if (!args || execve(path, args, environ) == -1)
			{
				perror("execve");
				exit(126);
			}
		}
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
