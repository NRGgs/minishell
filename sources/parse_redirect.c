/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:25:28 by nmattos           #+#    #+#             */
/*   Updated: 2025/01/27 14:34:20 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*	Returns the type of redirection.
 *
 *	str:	token to check
 *
 *	Return: type of redirection.
 */
static int	get_redirection_type(char *str)
{
	if (str != NULL && (ft_strcmp(str, ">") == 0 || ft_strcmp(str, "<") == 0))
	{
		return (TEXTFILE);
	}
	else if (str != NULL && (ft_strcmp(str, "<<") == 0))
	{
		return (HERE_DOC);
	}
	else if (str != NULL && ft_strcmp(str, ">>") == 0)
	{
		return (APPEND);
	}
	else if (str != NULL && ft_strcmp(str, "|") == 0)
	{
		return (PIPE);
	}
	else if (str != NULL && (str[0] == '\'' || str[0] == '\"'))
	{
		return (STRING);
	}
	return (STD);
}

/*	Parses redirections before the command and sets input type and filename.
 *
 *	input:	user input split by ' '
 *	i:		index of current token
 *	last:	last command in linked list
 *
 *	Return: SUCCESS (1) / FAIL (0).
 */
static int	before_command(char **input, int i, t_command **last)
{
	int	type;

	if (i <= 0 || get_redirection_type(input[i]) == STD)
		return (SUCCESS);
	type = get_redirection_type(input[i]);
	if (type == TEXTFILE || type == APPEND)
	{
		if (textfile_redirection(input[i - 1], input[i], last, BEFORE) == FAIL)
			return (FAIL);
	}
	else if (type == PIPE)
	{
		(*last)->in_type = PIPE;
	}
	else if (type == HERE_DOC || type == STRING)
	{
		return (FAIL);
	}
	return (SUCCESS);
}

/*	Parses redirections after the command and sets output type and filename.
 *
 *	input:	user input split by ' '
 *	i:		index of current token
 *	last:	last command in linked list
 *
 *	Return: SUCCESS (1) / FAIL (0).
 */
static int	after_command(char **input, int *i, t_command **last)
{
	int	type;

	if (input[*i + 1] == NULL || get_redirection_type(input[*i + 1]) == STD)
		return (SUCCESS);
	(*i)++;
	type = get_redirection_type(input[*i]);
	if (type == TEXTFILE)
	{
		if (textfile_redirection(input[*i + 1], input[*i], last, AFTER) == FAIL)
			return (FAIL);
		*i += 1;
	}
	else if (type == HERE_DOC)
	{
		if (here_doc_redirection(input[*i + 1], last) == FAIL)
			return (FAIL);
		*i += 1;
	}
	else if (type == PIPE)
		(*last)->out_type = PIPE;
	else if (type == STRING)
		if (string_redirection(input, last, i) == FAIL)
			return (FAIL);
	return (SUCCESS);
}

/*	Parses redirections and sets in/out types and filenames.
 *
 *	input: user input split by ' '
 *	cmds: linked list of commands
 *	i: index of current token
 *	command_index: index of command token
 *
 *	Return: SUCCESS (1) / FAIL (0).
 */
int	parse_redirect(char **input, t_command **cmds, int *i, int command_index)
{
	t_command	*last;

	last = cmd_last(*cmds);
	if (before_command(input, command_index - 1, &last) == FAIL)
		return (FAIL);
	if (after_command(input, i, &last) == FAIL)
		return (FAIL);
	if (last->in_type == HERE_DOC)
	{
		if (after_command(input, i + 1, &last) == FAIL)
			return (FAIL);
	}
	return (SUCCESS);
}
