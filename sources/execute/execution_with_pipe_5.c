/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_with_pipe_5.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:40:23 by iriadyns          #+#    #+#             */
/*   Updated: 2025/03/06 09:56:22 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern char	**environ;

static int	prepare_path_and_pipe(t_command *current,
				int *pipe_fd, t_shell *shell, char **path)
{
	*path = true_path(current->command, current->env_list, shell);
	if (current->next && setup_pipe_if_needed(current, pipe_fd) == FAIL)
	{
		free(*path);
		return (FAIL);
	}
	return (SUCCESS);
}

static int	fork_error_cleanup(t_command *current, char *path, int pipe_fd[2])
{
	if (current->next)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	free(path);
	return (FAIL);
}

static void	fill_child_data(t_child_data *child_data, t_command *current,
				int pipe_fd[2], t_shell *shell)
{
	child_data->current = current;
	child_data->pipe_fd[0] = pipe_fd[0];
	child_data->pipe_fd[1] = pipe_fd[1];
	child_data->shell = shell;
}

int	process_single_command(t_command *current, int *pipe_in, t_shell *shell)
{
	int				pipe_fd[2];
	pid_t			pid;
	char			*path;
	t_child_data	child_data;

	if (prepare_path_and_pipe(current, pipe_fd, shell, &path) == FAIL)
		return (FAIL);
	pid = fork();
	if (pid < 0)
		return (fork_error_cleanup(current, path, pipe_fd));
	else if (pid == 0)
	{
		child_data.pipe_in = pipe_in;
		child_data.path = path;
		fill_child_data(&child_data, current, pipe_fd, shell);
		child_branch(&child_data);
	}
	else
	{
		parent_branch(current, pipe_in, pipe_fd);
		free(path);
	}
	return (SUCCESS);
}

char	*handle_double_spaces(const char *str)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*new_str;

	len = strlen(str);
	i = 0;
	j = 0;
	new_str = malloc(3 * len + 1);
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == ' ' && str[i + 1] == ' ')
		{
			new_str[j++] = ' ';
			new_str[j++] = '\001';
			new_str[j++] = ' ';
			i += 2;
		}
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}
