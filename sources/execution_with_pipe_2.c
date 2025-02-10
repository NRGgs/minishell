/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_with_pipe_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:13:56 by iriadyns          #+#    #+#             */
/*   Updated: 2025/02/10 18:48:57 by iriadyns         ###   ########.fr       */
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

int	execution_with_pipe(t_command *commands)
{
	int			pipe_in;
	t_command	*current;

	pipe_in = STDIN_FILENO;
	current = commands;
	while (current)
	{
		if (process_single_command(current, &pipe_in) == FAIL)
			return (SHELL_CONTINUE);
		current = current->next;
	}
	wait_for_children();
	return (SHELL_CONTINUE);
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
