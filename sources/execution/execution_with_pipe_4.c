/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_with_pipe_4.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:22:32 by iriadyns          #+#    #+#             */
/*   Updated: 2025/02/21 11:13:44 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern char	**environ;

/**
 * @brief Processes redirections for a command or exits on failure.
 *
 * @param current The current command structure.
 */
static void	process_redir_or_exit(t_command *current)
{
	if (process_redirections(current) == ERROR)
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
static void	handle_builtin_pipe(t_command **cmd_ptr, char *path)
{
	t_env	*env_copy;
	int		builtin_ret;

	env_copy = (*cmd_ptr)->env_list;
	builtin_ret = execute_builtin(cmd_ptr);
	clean_commands(cmd_ptr);
	free(path);
	clear_env_list(env_copy);
	exit(builtin_ret);
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
static void	handle_external_pipe(t_command **cmd_ptr, char *path)
{
	char	**args;

	if (!path)
	{
		clean_commands(cmd_ptr);
		exit(127);
	}
	args = build_execve_args(*cmd_ptr);
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

/**
 * @brief Executes a command in a pipeline.
 * Processes redirections and then dispatches to either the built-in
 * or external pipe handler.
 *
 * @param current The current command structure.
 *
 * @param path The path to the executable.
 */
void	execute_command_pipe(t_command *current, char *path)
{
	process_redir_or_exit(current);
	if (is_builtin(current->command))
		handle_builtin_pipe(&current, path);
	else
		handle_external_pipe(&current, path);
}
