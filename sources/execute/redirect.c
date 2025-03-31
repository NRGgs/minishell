/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 10:37:30 by iriadyns          #+#    #+#             */
/*   Updated: 2025/03/31 08:00:15 by iriadyns         ###   ########.fr       */
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
		fd = open(filename, O_CREAT | O_WRONLY, 0644);
		if (fd == -1)
		{
			perror("Error creating input file");
			return (-1);
		}
		close(fd);
		fd = open(filename, O_RDONLY);
		if (fd == -1)
		{
			perror("Error opening input file after creation");
			return (-1);
		}
	}
	else
	{
		perror("Error opening input file");
		return (-1);
	}
	return (fd);
}

int	process_redirections(t_command *cmd, t_shell *shell)
{
	t_redirect	*redir;
	int			fd;
	int			flags;

	redir = cmd->redirect;
	while (redir)
	{
		if (!redir->arg || redir->arg[0] == '\0')
		{
			ft_putstr_fd("minishell: syntax error near unexpected token 'newline'\n", 2);
			shell->exit_status = 2;
			return (ERROR);
		}
		if (prepare_arg(cmd->env_list, &redir->arg, shell) == FAIL)
		{
			ft_putstr_fd("Error: Failed to prepare redirection argument\n", 2);
			return (ERROR);
		}
		if (redir->is_input)
		{
			fd = open_input_file(redir->arg);
			if (fd == -1)
				return (ERROR);
			if (dup2(fd, STDIN_FILENO) == -1)
			{
				close(fd);
				return (ERROR);
			}
			close(fd);
		}
		else
		{
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
		}
		redir = redir->next;
	}
	return (SUCCESS);
}