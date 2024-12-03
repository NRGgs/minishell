/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_redirect.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmattos <nmattos@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/03 14:25:28 by nmattos       #+#    #+#                 */
/*   Updated: 2024/12/03 15:55:40 by nmattos       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"

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
	return (STD);
}

static int	before_command(char **input, int i, t_command **last)
{
	int	type;

	if (i == 0 || get_redirection_type(input[i]) == STD)
		return (SUCCESS);
	i -= 1;
	type = get_redirection_type(input[i]);
	if (type == TEXTFILE || type == APPEND)
	{
		if (textfile_redirection(input[i - 1], input[i], last) == FAIL)
			return (FAIL);
	}
	else if (type == PIPE)
	{
		(*last)->in_type = PIPE;
	}
	else if (type == HERE_DOC)
	{
		return (FAIL);
	}
	return (SUCCESS);
}

static int	after_command(char **input, int *i, t_command **last)
{
	int	type;

	if (input[*i] == NULL || get_redirection_type(input[*i]) == STD)
		return (SUCCESS);
	type = get_redirection_type(input[*i]);
	if (type == TEXTFILE)
	{
		if (textfile_redirection(input[*i + 1], input[*i], last) == FAIL)
			return (FAIL);
		*i += 1;
	}
	else if (type == PIPE)
	{
		(*last)->out_type = PIPE;
	}
	else if (type == HERE_DOC)
	{
		if (here_doc_redirection(input[*i + 1], last) == FAIL)
			return (FAIL);
		*i += 1;
	}
	return (SUCCESS);
}

int	parse_redirect(char **input, t_command **cmds, int *i, int command_index)
{
	t_command	*last;

	last = cmd_last(*cmds);
	if (before_command(input, command_index, &last) == FAIL)
		return (FAIL);
	if (after_command(input, i, &last) == FAIL)
		return (FAIL);
	return (SUCCESS);
}
