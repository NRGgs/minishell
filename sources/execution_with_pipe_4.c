/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_with_pipe_4.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:22:32 by iriadyns          #+#    #+#             */
/*   Updated: 2025/02/17 13:30:39 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**environ;

static void	process_redir_or_exit(t_command *current)
{
	if (process_redirections(current) == ERROR)
	{
		ft_putstr_fd("Error: Redirection failed.\n", 2);
		exit(1);
	}
}

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

void	execute_command_pipe(t_command *current, char *path)
{
	process_redir_or_exit(current);
	if (is_builtin(current->command))
		handle_builtin_pipe(&current, path);
	else
		handle_external_pipe(&current, path);
}
