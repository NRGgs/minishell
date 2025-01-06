/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 10:37:30 by iriadyns          #+#    #+#             */
/*   Updated: 2024/12/23 12:25:38 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int handle_input_redirection(t_command *cmd)
{
	int fd;

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

int handle_output_redirection(t_command *cmd)
{
	int fd;
	int flags;

	flags = (cmd->out_type == APPEND) ? (O_WRONLY | O_CREAT | O_APPEND) : (O_WRONLY | O_CREAT | O_TRUNC);
	fd = open(cmd->output, flags, 0644);
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

int handle_heredoc(t_command *cmd)
{
	int pipefd[2];
	char *line;

	if (pipe(pipefd) == -1)
	{
		perror("Error creating pipe for heredoc");
		return (ERROR);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, cmd->input) == 0)
			break;
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	free(line);
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror("Error duplicating file descriptor for heredoc");
		close(pipefd[0]);
		return (ERROR);
	}
	close(pipefd[0]);
	return (SUCCESS);
}

int process_redirections(t_command *cmd)
{
	if (cmd->in_type == TEXTFILE && handle_input_redirection(cmd) == ERROR)
		return (ERROR);
	if (cmd->in_type == HERE_DOC && handle_heredoc(cmd) == ERROR)
		return (ERROR);
	if ((cmd->out_type == TEXTFILE || cmd->out_type == APPEND) && handle_output_redirection(cmd) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
