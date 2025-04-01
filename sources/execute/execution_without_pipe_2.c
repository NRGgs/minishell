/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_without_pipe_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:53:50 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/01 16:04:20 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern char	**environ;

int	execution_without_pipe(t_command *commands, t_shell *shell)
{
	int	backup_in;
	int	backup_out;

	if (handle_dollar_commands(commands, shell))
		return (SHELL_CONTINUE);
	handle_special_commands_in_structure(commands, shell->env_list, shell);
	if (!commands)
		return (ft_putstr_fd("Error: Invalid command structure.\n", 2),
			SHELL_CONTINUE);
	if (!commands->command || commands->command[0] == '\0')
	{
		if (commands->redirect)
		{
			backup_in = dup(STDIN_FILENO);
			backup_out = dup(STDOUT_FILENO);
			if (process_redirections(commands, shell) == ERROR)
				return (restore_fds(backup_in, backup_out), SHELL_CONTINUE);
			restore_fds(backup_in, backup_out);
		}
		return (SHELL_CONTINUE);
	}
	if (is_builtin(commands->command))
		return (exec_builtin_no_pipe(commands, shell));
	return (exec_external_no_pipe(commands, shell));
}

bool	has_here_doc(t_command *cmd)
{
	t_redirect *redir = cmd->redirect;
	while (redir)
	{
		if (redir->is_input && redir->type == HERE_DOC)
			return (true);
		redir = redir->next;
	}
	return (false);
}

static void	handle_here_doc(t_command *commands, t_shell *shell)
{
	char	*filename;
	int		fd;

	filename = create_heredoc_file(commands->pattern, commands->env_list, shell);
	if (!filename)
		exit(1);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		free(filename);
		exit(1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		free(filename);
		exit(1);
	}
	close(fd);
	unlink(filename);
	free(filename);
}

void	handle_child_process(t_command *commands, char *path,
		char *args[], t_shell *shell)
{
	if (process_redirections(commands, shell) == ERROR)
		exit(1);
	if (has_here_doc(commands))
		handle_here_doc(commands, shell);
	if (!path)
		exit(127);
	if (execve(path, args, environ) == -1)
		exit(126);
}