/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 10:37:30 by iriadyns          #+#    #+#             */
/*   Updated: 2025/03/24 16:26:35 by iriadyns         ###   ########.fr       */
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
		return (perror("Error opening input file"), -1);
	return (fd);
}

int	handle_input_redirection(t_command *cmd, t_shell *shell)
{
	int	fd;

	if (prepare_arg(cmd->env_list, &cmd->input, shell) == FAIL)
	{
		ft_putstr_fd("Error: Failed to prepare output argument\n", 2);
		return (ERROR);
	}
	fd = open_input_file(cmd->input);
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

/**
 * @brief Handles output redirection for a command.
 * Opens the output file (in append or truncate mode)
 * and duplicates its file descriptor to stdout.
 *
 * @param cmd The command structure.
 *
 * @return SUCCESS on success, ERROR on failure.
 */
int	handle_output_redirection(t_command *cmd, t_shell *shell)
{
	int	fd;
	int	flags;

	if (prepare_arg(cmd->env_list, &cmd->output, shell) == FAIL)
	{
		ft_putstr_fd("Error: Failed to prepare output argument\n", 2);
		return (ERROR);
	}
	if (cmd->out_type == APPEND)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(cmd->output, flags, 0777);
	if (fd == -1)
		return (perror("Error opening output file"), ERROR);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("Error duplicating file descriptor for output");
		return (close(fd), ERROR);
	}
	return (close(fd), SUCCESS);
}

/**
 * @brief Processes all redirections for a command.
 *
 * @param cmd The command structure.
 *
 * @return SUCCESS on success, ERROR on failure.
 */
int	process_redirections(t_command *cmd, t_shell *shell)
{
	if (cmd->in_type == TEXTFILE)
	{
		if (handle_input_redirection(cmd, shell) == ERROR)
			return (ERROR);
	}
	if ((cmd->output && ft_strlen(cmd->output) > 0)
		|| (cmd->out_type == TEXTFILE || cmd->out_type == APPEND))
	{
		if (handle_output_redirection(cmd, shell) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}
