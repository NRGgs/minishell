/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 10:37:30 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/02 16:51:51 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	open_input_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd != -1)
		return (fd);
	if (errno == ENOENT)
	{
		printf("minishell: %s: No such file or directory\n", filename);
		return (-1);
	}
	else
	{
		perror("Error opening input file");
		return (-1);
	}
}

static int	process_input_redirection(t_redirect *redir)
{
	int	fd;

	fd = open_input_file(redir->arg);
	if (fd == -1)
		return (ERROR);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		return (ERROR);
	}
	close(fd);
	return (SUCCESS);
}

static int	process_output_redirection(t_redirect *redir)
{
	int	fd;
	int	flags;

	if (redir->type == APPEND)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(redir->arg, flags, 0777);
	if (fd == -1)
	{
		perror("Error opening output file");
		return (ERROR);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		perror("Error duplicating file descriptor for output");
		return (ERROR);
	}
	close(fd);
	return (SUCCESS);
}

static int	validate_redirection(t_redirect *redir, t_shell *shell)
{
	if (!redir->arg || redir->arg[0] == '\0')
	{
		ft_putstr_fd("minishell: syntax error near"
			"unexpected token 'newline'\n", 2);
		shell->exit_status = 2;
		return (ERROR);
	}
	return (SUCCESS);
}

int	process_redirections(t_command *cmd, t_shell *shell)
{
	t_redirect	*redir;

	redir = cmd->redirect;
	while (redir)
	{
		if (redir->type == PIPE || (redir->is_input && redir->type == HERE_DOC))
		{
			redir = redir->next;
			continue ;
		}
		if (validate_redirection(redir, shell) == ERROR)
			return (ERROR);
		if (redir->is_input)
		{
			if (process_input_redirection(redir) != SUCCESS)
				return (ERROR);
		}
		else
		{
			if (process_output_redirection(redir) != SUCCESS)
				return (ERROR);
		}
		redir = redir->next;
	}
	return (SUCCESS);
}
