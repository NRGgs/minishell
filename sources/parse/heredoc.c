/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:10:41 by nmattos-          #+#    #+#             */
/*   Updated: 2025/03/31 10:54:58 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	read_here_doc(char *delimiter, char **input);
static char	*strjoin_free(char **s1, char *s2);

/**
 * Handles here_doc redirection.
 *
 * @param delimiter string to delimit the input
 * @param last linked list of commands
 * @return SUCCESS (1) / FAIL (0)
 */
int	here_doc_redirection(char *delimiter, t_command **last)
{
	char	*input;

	redirect_last((*last)->redirect)->type = HERE_DOC;
	input = ft_calloc(1, 1);
	if (input == NULL)
		return (FAIL);
	if (read_here_doc(delimiter, &input) == FAIL)
		return (FAIL);
	(*last)->pattern = input;
	return (SUCCESS);
}

/**
 * Reads input from user until delimiter is found.
 *
 * @param delimiter string to delimit the input
 * @param input string to store the input
 * @return SUCCESS (1) / FAIL (0)
 */
static int	read_here_doc(char *delimiter, char **input)
{
	char	*buffer;
	char	*temp;
	int		stdin_backup;

	stdin_backup = dup(STDIN_FILENO);
	signal(SIGINT, signal_heredoc);
	while (1)
	{
		buffer = readline("> ");
		if (buffer == NULL)
			return (restore_stdin(stdin_backup, input));
		if (ft_strcmp(buffer, delimiter) == 0)
			return (free(buffer), SUCCESS);
		*input = add_newline(*input);
		if (*input == NULL)
			return (free(buffer), FAIL);
		temp = strjoin_free(input, buffer);
		if (temp == NULL)
			return (FAIL);
		*input = ft_strdup(temp);
		free(temp);
		if (*input == NULL)
			return (FAIL);
	}
	return (SUCCESS);
}

char	*create_heredoc_file(char *input, t_env *env_list, t_shell *shell)
{
	int		fd;
	char	*fn;
	ssize_t	bytes_written;

	fn = ft_strdup("heredoc");
	if (fn == NULL)
		return (NULL);
	fd = open(fn, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (free(fn), NULL);
	if (handle_variables(env_list, &input, shell) == FAIL)
	{
		close(fd);
		return (free(fn), NULL);
	}
	bytes_written = write(fd, input, ft_strlen(input));
	write(fd, "\n", 1);
	if (bytes_written == -1 || bytes_written != (ssize_t)ft_strlen(input))
	{
		close(fd);
		return (free(fn), NULL);
	}
	close(fd);
	return (fn);
}

/**
 * Joins two strings and frees both.
 *
 * @param s1 string to join
 * @param s2 string to join
 * @return new string
 */
static char	*strjoin_free(char **s1, char *s2)
{
	char	*temp;

	temp = ft_strjoin(*s1, s2);
	free_null((void **)s1);
	free(s2);
	return (temp);
}

/**
 * Restores stdin to its original file descriptor.
 *
 * @param stdin_backup file descriptor to restore
 * @param input string to free
 * @return SUCCESS (1)
 */
int	restore_stdin(int stdin_backup, char **input)
{
	dup2(stdin_backup, STDIN_FILENO);
	close(stdin_backup);
	free_null((void **)input);
	return (FAIL);
}
