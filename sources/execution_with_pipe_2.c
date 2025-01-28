/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_with_pipe_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:13:56 by iriadyns          #+#    #+#             */
/*   Updated: 2025/01/28 12:53:09 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**environ;

void	handle_child(t_command *current, int pipe_in, int *pipe_fd, char *path)
{
	setup_input_output(current, pipe_in, pipe_fd);
	execute_command_pipe(current, path);
}

void	handle_parent(int *pipe_fd, int *pipe_in)
{
	close(pipe_fd[1]);
	*pipe_in = pipe_fd[0];
}

// void	execution_with_pipe(t_command *commands)
// {
// 	int			pipe_fd[2];
// 	int			pipe_in;
// 	t_command	*current;
// 	char		*path;
// 	pid_t		pid;

// 	pipe_in = STDIN_FILENO;
// 	current = commands;
// 	while (current)
// 	{
// 		path = true_path(current->command, environ);
// 		if (current->next && pipe(pipe_fd) == -1)
// 		{
// 			perror("pipe");
// 			return ;
// 		}
// 		pid = fork();
// 		if (pid < 0)
// 		{
// 			perror("fork");
// 			return ;
// 		}
// 		else if (pid == 0)
// 			handle_child(current, pipe_in, pipe_fd, path);
// 		else
// 			handle_parent(pipe_fd, &pipe_in);
// 		current = current->next;
// 	}
// 	while (wait(NULL) > 0)
// 		;
// }

int	process_single_command(t_command *current, int *pipe_in)
{
	char	*path;
	int		pipe_fd[2];
	pid_t	pid;

	path = true_path(current->command, environ);
	if (current->next && pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (FAIL);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (FAIL);
	}
	else if (pid == 0)
		handle_child(current, *pipe_in, pipe_fd, path);
	else
		handle_parent(pipe_fd, pipe_in);
	return (SUCCESS);
}

void	execution_with_pipe(t_command *commands)
{
	int			pipe_in;
	t_command	*current;

	pipe_in = STDIN_FILENO;
	current = commands;
	while (current)
	{
		if (process_single_command(current, &pipe_in) == FAIL)
			return ;
		current = current->next;
	}
	wait_for_children();
}

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
