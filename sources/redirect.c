/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 10:37:30 by iriadyns          #+#    #+#             */
/*   Updated: 2025/01/28 12:37:00 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_input_redirection(t_command *cmd)
{
	int	fd;

	fd = open(cmd->input, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening input file");
		return (ERROR);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("Error duplicating file descriptor for input");
		close(fd);
		return (ERROR);
	}
	close(fd);
	return (SUCCESS);
}

int	handle_output_redirection(t_command *cmd)
{
	int	fd;
	int	flags;

	if (cmd->out_type == APPEND)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(cmd->output, flags, 0777);
	if (fd == -1)
	{
		perror("Error opening output file");
		return (ERROR);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("Error duplicating file descriptor for output");
		close(fd);
		return (ERROR);
	}
	close(fd);
	return (SUCCESS);
}

int	process_redirections(t_command *cmd)
{
	if (cmd->in_type == TEXTFILE)
	{
		if (handle_input_redirection(cmd) == ERROR)
			return (ERROR);
	}
	if (cmd->out_type == TEXTFILE || cmd->out_type == APPEND)
	{
		if (handle_output_redirection(cmd) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}
