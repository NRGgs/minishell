/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_without_pipe_3.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:33:54 by iriadyns          #+#    #+#             */
/*   Updated: 2025/03/06 10:38:44 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*prepare_heredoc(t_command *cmd)
{
	char	*saved;

	saved = NULL;
	if (cmd->in_type == HERE_DOC)
	{
		saved = ft_strdup(cmd->pattern);
		if (!saved)
			return (NULL);
		free(cmd->pattern);
		cmd->pattern = ft_strdup("");
		if (!cmd->pattern)
		{
			free(saved);
			return (NULL);
		}
	}
	return (saved);
}

static void	restore_heredoc(t_command *cmd, char *saved)
{
	if (cmd->in_type == HERE_DOC && saved)
	{
		free(cmd->pattern);
		cmd->pattern = saved;
	}
}

static int	cleanup_and_return(char *path, char *heredoc,
				int exit_status, t_shell *shell)
{
	if (path)
		free(path);
	if (heredoc)
		free(heredoc);
	shell->exit_status = exit_status;
	return (SHELL_CONTINUE);
}

int	exec_external_no_pipe(t_command *commands, t_shell *shell)
{
	char	**args;
	char	*path;
	char	*heredoc_content;

	heredoc_content = prepare_heredoc(commands);
	path = true_path(commands->command, commands->env_list, shell);
	if (!path)
		return (cleanup_and_return(NULL, heredoc_content,
				CMD_NOT_FOUND, shell));
	args = build_execve_args(commands, shell);
	if (!args)
		return (cleanup_and_return(path, heredoc_content,
				CMD_NOT_FOUND, shell));
	restore_heredoc(commands, heredoc_content);
	execute_command(commands, path, args, shell);
	free(path);
	free_2d_array(args);
	return (SHELL_CONTINUE);
}
