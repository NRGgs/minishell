/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_without_pipe_3.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:33:54 by iriadyns          #+#    #+#             */
/*   Updated: 2025/03/31 07:59:46 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*prepare_heredoc(t_command *cmd)
{
	char		*saved;
	t_redirect	*redir;

	saved = NULL;
	redir = cmd->redirect;
	while (redir)
	{
		if (redir->is_input && redir->type == HERE_DOC)
		{
			saved = ft_strdup(redir->arg);
			if (!saved)
				return (NULL);
			free(redir->arg);
			redir->arg = ft_strdup("");
			if (!redir->arg)
			{
				free(saved);
				return (NULL);
			}
			break;
		}
		redir = redir->next;
	}
	return (saved);
}

static void	restore_heredoc(t_command *cmd, char *saved)
{
	t_redirect	*redir;

	redir = cmd->redirect;
	while (redir)
	{
		if (redir->is_input && redir->type == HERE_DOC && saved)
		{
			free(redir->arg);
			redir->arg = saved;
			break;
		}
		redir = redir->next;
	}
}


static int	cleanup_and_return(char *path, char *heredoc)
{
	if (path)
		free(path);
	if (heredoc)
		free(heredoc);
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
		return (cleanup_and_return(NULL, heredoc_content));
	args = build_execve_args(commands, shell);
	if (!args)
		return (cleanup_and_return(path, heredoc_content));
	restore_heredoc(commands, heredoc_content);
	execute_command(commands, path, args, shell);
	free(path);
	free_2d_array(args);
	return (SHELL_CONTINUE);
}
