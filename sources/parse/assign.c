/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   assign.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmattos- <nmattos-@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/25 15:48:25 by nmattos       #+#    #+#                 */
/*   Updated: 2025/03/30 12:57:37 by nmattos       ########   odam.nl         */
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
		add_redirect(&(*cmd)->redirect, new_redirect(APPEND, false, NULL));
	else if (ft_strncmp(redirection, "<<", 2) == 0)
		add_redirect(&(*cmd)->redirect, new_redirect(HERE_DOC, true, NULL));
	else if (redirection[0] == '>')
		add_redirect(&(*cmd)->redirect, new_redirect(TEXTFILE, false, NULL));
	else if (redirection[0] == '<')
		add_redirect(&(*cmd)->redirect, new_redirect(TEXTFILE, true, NULL));
}

static int	set_filename(t_command **cmd, t_token *tokens, t_token **current)
{
	char	*word;

	if (redirect_last((*cmd)->redirect)->type == TEXTFILE
		&& prev_token(tokens, *current)->type == E_REDIRECTION)
	{
		word = ft_strndup((*current)->token, ft_strlen((*current)->token));
		if (word == NULL)
			return (FAIL);
		redirect_last((*cmd)->redirect)->arg = word;
	}
	else if (redirect_last((*cmd)->redirect)->type == HERE_DOC)
	{
		if (here_doc_redirection((*current)->token, cmd) == FAIL)
			return (FAIL);
	}
	else if (redirect_last((*cmd)->redirect)->type == TEXTFILE
			|| redirect_last((*cmd)->redirect)->type == APPEND)
	{
		word = ft_strndup((*current)->token, ft_strlen((*current)->token));
		if (word == NULL)
			return (FAIL);
		redirect_last((*cmd)->redirect)->arg = word;
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
