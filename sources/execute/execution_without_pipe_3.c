/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_without_pipe_3.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:07:57 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/01 16:08:00 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*prepare_heredoc(t_command *cmd)
{
	char		*saved;
	t_redirect	*redir;

	saved = NULL;
	redir = cmd->redirect;
	while (redir)
	{
		if (redir->is_input && redir->type == HERE_DOC)
		{
			if (!cmd->pattern || cmd->pattern[0] == '\0')
			{
				ft_putstr_fd("minishell: syntax error near"
					"unexpected token `newline'\n", 2);
				return (NULL);
			}
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
			break ;
		}
		redir = redir->next;
	}
	return (saved);
}

void	restore_heredoc(t_command *cmd, char *saved)
{
	t_redirect	*redir;

	if (!saved)
		return ;
	redir = cmd->redirect;
	while (redir)
	{
		if (redir->is_input && redir->type == HERE_DOC)
		{
			if (redir->arg)
				free(redir->arg);
			redir->arg = ft_strdup(saved);
			if (cmd->pattern)
			{
				free(cmd->pattern);
				cmd->pattern = ft_strdup(saved);
			}
			break ;
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
