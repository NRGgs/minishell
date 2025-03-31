/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_with_pipe_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:03:19 by iriadyns          #+#    #+#             */
/*   Updated: 2025/03/31 10:21:13 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static int	has_output_redirection(t_command *cmd)
{
	t_redirect *redir = cmd->redirect;
	while (redir)
	{
		if (!redir->is_input && redir->type != PIPE)
			return (1);
		redir = redir->next;
	}
	return (0);
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
		if (!has_output_redirection(current))
		{
			if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			{
				perror("dup2");
				exit(1);
			}
		}
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

/**
 * @brief Waits for all child processes to finish.
 */
void	wait_for_children(void)
{
	while (wait(NULL) > 0)
		;
}
