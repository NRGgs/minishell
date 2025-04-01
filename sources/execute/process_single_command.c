/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_single_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:30:20 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/01 12:54:32 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_cmd_validity(t_command *current, t_shell *shell)
{
	if (!current->command || current->command[0] == '\0')
	{
		ft_putstr_fd("minishell: syntax"
			"error near unexpected token `newline'\n", 2);
		shell->exit_status = 2;
		return (FAIL);
	}
	return (SUCCESS);
}

static int	child_helper(t_command *current, int *pipe_in, int pipe_fd[2],
							t_exec_data *ctx)
{
	t_child_data	child;

	child.pipe_in = pipe_in;
	child.path = ctx->path;
	fill_child_data(&child, current, pipe_fd, ctx->shell);
	child_branch(&child);
	return (SUCCESS);
}

static void	parent_helper(int *pipe_fd, int *pipe_in, char *path)
{
	handle_parent(pipe_fd, pipe_in);
	free(path);
}

int	process_single_command(t_command *current, int *pipe_in, t_shell *shell)
{
	int			pipe_fd[2];
	pid_t		pid;
	char		*path;
	t_exec_data	ctx;

	if (check_cmd_validity(current, shell) == FAIL)
		return (SHELL_CONTINUE);
	if (prepare_path_and_pipe(current, pipe_fd, shell, &path) == FAIL)
		return (FAIL);
	ctx.path = path;
	ctx.shell = shell;
	pid = fork();
	if (pid < 0)
		return (fork_error_cleanup(current, path, pipe_fd));
	if (pid == 0)
		return (child_helper(current, pipe_in, pipe_fd, &ctx));
	else
	{
		if (current->next)
			parent_helper(pipe_fd, pipe_in, path);
		else
			free(path);
	}
	return (SUCCESS);
}
