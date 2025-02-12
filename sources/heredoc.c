/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:10:41 by nmattos-          #+#    #+#             */
/*   Updated: 2025/02/12 12:22:40 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	read_here_doc(char *delimiter, char **input);
static char	*strjoin_free(char **s1, char *s2);
static int	restore_stdin(int stdin_backup, char **input);

/*	Handles here_doc redirection.
 *
 *	delimiter:	string to delimit the input
 *	last:		linked list of commands
 *
 *	Return: SUCCESS (1) / FAIL (0).
 */
int	here_doc_redirection(char *delimiter, t_command **last)
{
	char	*input;

	(*last)->in_type = HERE_DOC;
	input = ft_calloc(1, 1);
	if (input == NULL)
		return (FAIL);
	if (read_here_doc(delimiter, &input) == FAIL)
		return (FAIL);
	(*last)->pattern = input;
	return (SUCCESS);
}

/*	Reads input from user until delimiter is found.
 *
 *	delimiter:	string to delimit the input
 *	input:		string to store the input
 *
 *	Return:		new string (input).
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
		buffer = readline("heredoc> ");
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

/*	Joins two strings and frees both.
 *
 *	s1:		string to join
 *	s2:		string to join
 *
 * 	Return:	new string.
 */
static char	*strjoin_free(char **s1, char *s2)
{
	char	*temp;

	temp = ft_strjoin(*s1, s2);
	free_null((void **)s1);
	free(s2);
	return (temp);
}

/*	Restores stdin to its original file descriptor.
 *
 *	stdin_backup:	file descriptor to restore
 *	input:			string to free
 *
 * 	Return: SUCCESS (1).
 */
static int	restore_stdin(int stdin_backup, char **input)
{
	dup2(stdin_backup, STDIN_FILENO);
    close(stdin_backup);
	free_null((void **)input);
	return (SUCCESS);
}
