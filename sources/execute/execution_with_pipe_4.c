/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_with_pipe_4.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:22:32 by iriadyns          #+#    #+#             */
/*   Updated: 2025/03/06 12:41:21 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern char	**environ;

/**
 * @brief Processes redirections for a command or exits on failure.
 *
 * @param current The current command structure.
 */
void	process_redir_or_exit(t_command *current, t_shell *shell)
{
	if (process_redirections(current, shell) == ERROR)
	{
		ft_putstr_fd("Error: Redirection failed.\n", 2);
		exit(1);
	}
}

/**
 * @brief Handles the execution of a built-in command in a pipeline.
 * Executes the built-in, cleans up the command structure, frees resources,
 * and exits with the built-in's exit status.
 *
 * @param cmd_ptr Pointer to the pointer of the current command.
 *
 * @param path The path to the executable (unused for built-ins).
 */
void	handle_builtin_pipe(t_command **cmd_ptr, char *path, t_shell *shell)
{
	t_env	*env_copy;
	int		builtin_ret;

	env_copy = (*cmd_ptr)->env_list;
	builtin_ret = execute_builtin(cmd_ptr, shell);
	clean_commands(cmd_ptr);
	free(path);
	clear_env_list(env_copy);
	exit(builtin_ret);
}

char	**get_args_without_heredoc(t_command *cmd)
{
	char	*saved_pattern;
	char	**args;

	saved_pattern = NULL;
	if (cmd->in_type == HERE_DOC && cmd->pattern && ft_strlen(cmd->pattern) > 0)
	{
		saved_pattern = ft_strdup(cmd->pattern);
		if (!saved_pattern)
			return (NULL);
		free(cmd->pattern);
		cmd->pattern = ft_strdup("");
		if (!cmd->pattern)
		{
			free(saved_pattern);
			return (NULL);
		}
	}
	args = get_command_args(cmd);
	if (saved_pattern)
	{
		free(cmd->pattern);
		cmd->pattern = saved_pattern;
	}
	return (args);
}

/**
 * @brief Handles the execution of an external command in a pipeline.
 * Builds the argument vector, executes the command via execve,
 * and frees resources on failure.
 *
 * @param cmd_ptr Pointer to the pointer of the current command.
 *
 * @param path The path to the executable.
 */
void	handle_external_pipe(t_command **cmd_ptr, char *path)
{
	char	**args;

	if (!path)
	{
		clean_commands(cmd_ptr);
		exit(127);
	}
	args = get_args_without_heredoc(*cmd_ptr);
	if (!args)
	{
		clean_commands(cmd_ptr);
		free(path);
		exit(1);
	}
	if (execve(path, args, environ) == -1)
	{
		free_2d_array(args);
		free(path);
		perror("execve");
		exit(126);
	}
}
