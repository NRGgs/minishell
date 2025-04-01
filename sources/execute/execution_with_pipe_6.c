/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_with_pipe_6.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:42:28 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/01 16:05:05 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_command_pipe(t_command *current, char *path, t_shell *shell)
{
	process_redir_or_exit(current, shell);
	if (has_here_doc(current))
		process_here_doc(current, shell);
	if (is_builtin(current->command))
		handle_builtin_pipe(&current, path, shell);
	else
		handle_external_pipe(&current, path, shell);
}

int	count_tokens(char **arr)
{
	int	cnt;

	cnt = 0;
	while (arr && arr[cnt])
		cnt++;
	return (cnt);
}

void	process_here_doc(t_command *current, t_shell *shell)
{
	int			fd;
	char		*filename;
	char		*saved;
	char		*heredoc_content;
	t_redirect	*redir;

	heredoc_content = NULL;
	saved = prepare_heredoc(current);
	if (!saved)
		exit(2);
	restore_heredoc(current, saved);
	redir = current->redirect;
	while (redir)
	{
		if (redir->is_input && redir->type == HERE_DOC)
		{
			heredoc_content = redir->arg;
			break ;
		}
		redir = redir->next;
	}
	if (!heredoc_content)
	{
		ft_putstr_fd("minishell: syntax error:"
			"missing here-doc delimiter\n", 2);
		free(saved);
		exit(2);
	}
	filename = create_heredoc_file(heredoc_content, current->env_list, shell);
	if (!filename)
	{
		free(saved);
		exit(1);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		free(filename);
		free(saved);
		exit(1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		free(filename);
		free(saved);
		exit(1);
	}
	close(fd);
	unlink(filename);
	free(filename);
	free(saved);
}
