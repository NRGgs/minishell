/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 10:37:30 by iriadyns          #+#    #+#             */
/*   Updated: 2025/02/17 14:59:06 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Handles input redirection for a command.
 * Opens the input file and duplicates its file descriptor to stdin.
 *
 * @param cmd The command structure.
 *
 * @return SUCCESS on success, ERROR on failure.
 */
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

/**
 * @brief Handles output redirection for a command.
 * Opens the output file (in append or truncate mode)
 * and duplicates its file descriptor to stdout.
 *
 * @param cmd The command structure.
 *
 * @return SUCCESS on success, ERROR on failure.
 */
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

/**
 * @brief Processes all redirections for a command.
 *
 * @param cmd The command structure.
 *
 * @return SUCCESS on success, ERROR on failure.
 */
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
