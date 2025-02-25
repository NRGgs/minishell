/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   assign.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmattos <nmattos@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/25 15:48:25 by nmattos       #+#    #+#                 */
/*   Updated: 2025/02/25 16:17:38 by nmattos       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	allocate_and_assign(t_command **cmd, t_token **tokens);
static void	set_redirection(t_command **cmd, char *redirection);
static int	set_filename(t_command **cmd, t_token *tokens);
static int	set_argument(char **arg, char *word);

int	assign_token(t_command **cmd, t_token **tokens)
{
	if ((*tokens)->type == E_COMMAND
		|| (*tokens)->type == E_OPTION
		|| (*tokens)->type == E_ARGUMENT)
	{
		if (allocate_and_assign(cmd, tokens) == FAIL)
			return (FAIL);
	}
	else if ((*tokens)->type == E_REDIRECTION)
		set_redirection(cmd, (*tokens)->token);
	else if ((*tokens)->type == E_FILENAME)
	{
		if (set_filename(cmd, *tokens) == FAIL)
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

static int	set_filename(t_command **cmd, t_token *tokens)
{
	char	*word;

	word = ft_strndup(tokens->token, ft_strlen(tokens->token));
	if (word == NULL)
		return (FAIL);
	if ((*cmd)->in_type == TEXTFILE
		&& previous_token(tokens, tokens)->type == E_REDIRECTION)
		(*cmd)->input = word;
	else if ((*cmd)->in_type == HERE_DOC)
	{
		if (here_doc_redirection(word, cmd) == FAIL)
			return (FAIL);
	}
	else if ((*cmd)->out_type == TEXTFILE)
		(*cmd)->output = word;
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
	*arg = temp;
	temp = ft_strjoin(*arg, word);
	if (temp == NULL)
		return (FAIL);
	*arg = temp;
	return (SUCCESS);
}
