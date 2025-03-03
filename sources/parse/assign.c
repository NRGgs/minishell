/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:48:25 by nmattos           #+#    #+#             */
/*   Updated: 2025/03/03 16:37:46 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	allocate_and_assign(t_command **cmd, t_token **tokens);
static void	set_redirection(t_command **cmd, char *redirection);
static int	set_filename(t_command **cmd, t_token *tokens, t_token **current);
static int	set_argument(char **arg, char *word);

int	assign_token(t_command **cmd, t_token **tokens, t_token **current)
{
	if ((*current)->type == E_COMMAND
		|| (*current)->type == E_OPTION
		|| (*current)->type == E_ARGUMENT)
	{
		if (allocate_and_assign(cmd, current) == FAIL)
			return (FAIL);
	}
	else if ((*current)->type == E_REDIRECTION)
		set_redirection(cmd, (*current)->token);
	else if ((*current)->type == E_FILENAME)
	{
		if (set_filename(cmd, *tokens, current) == FAIL)
			return (FAIL);
	}
	return (SUCCESS);
}

static int	allocate_and_assign(t_command **cmd, t_token **tokens)
{
	char	*word;

	word = ft_strndup((*tokens)->token, ft_strlen((*tokens)->token));
	if (word == NULL)
		return (FAIL);
	if ((*tokens)->type == E_COMMAND)
		(*cmd)->command = word;
	else if ((*tokens)->type == E_OPTION)
	{
		if (set_argument(&(*cmd)->options, word) == FAIL)
			return (free(word), FAIL);
	}
	else if ((*tokens)->type == E_ARGUMENT)
		if (set_argument(&(*cmd)->pattern, word) == FAIL)
			return (free(word), FAIL);
	return (SUCCESS);
}

static void	set_redirection(t_command **cmd, char *redirection)
{
	if (ft_strncmp(redirection, ">>", 2) == 0)
		(*cmd)->out_type = APPEND;
	else if (ft_strncmp(redirection, "<<", 2) == 0)
		(*cmd)->in_type = HERE_DOC;
	else if (redirection[0] == '>')
		(*cmd)->out_type = TEXTFILE;
	else if (redirection[0] == '<')
		(*cmd)->in_type = TEXTFILE;
}

static int	set_filename(t_command **cmd, t_token *tokens, t_token **current)
{
	char	*word;

	if ((*cmd)->in_type == TEXTFILE
		&& prev_token(tokens, *current)->type == E_REDIRECTION)
	{
		word = ft_strndup((*current)->token, ft_strlen((*current)->token));
		if (word == NULL)
			return (FAIL);
		(*cmd)->input = word;
	}
	else if ((*cmd)->in_type == HERE_DOC)
	{
		if (here_doc_redirection((*current)->token, cmd) == FAIL)
			return (FAIL);
	}
	else if ((*cmd)->out_type == TEXTFILE || (*cmd)->out_type == APPEND)
	{
		word = ft_strndup((*current)->token, ft_strlen((*current)->token));
		if (word == NULL)
			return (FAIL);
		(*cmd)->output = word;
	}
	return (SUCCESS);
}

static int	set_argument(char **arg, char *word)
{
	char	*temp;

	if (*arg == NULL)
	{
		*arg = word;
		return (SUCCESS);
	}
	temp = ft_strjoin(*arg, " ");
	if (temp == NULL)
		return (FAIL);
	free(*arg);
	*arg = ft_strndup(temp, ft_strlen(temp));
	if (*arg == NULL)
		return (FAIL);
	free(temp);
	temp = ft_strjoin(*arg, word);
	free(word);
	if (temp == NULL)
		return (FAIL);
	free(*arg);
	*arg = temp;
	return (SUCCESS);
}
