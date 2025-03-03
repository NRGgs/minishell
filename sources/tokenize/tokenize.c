/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:37:47 by nmattos           #+#    #+#             */
/*   Updated: 2025/03/03 16:49:24 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	create_token(char **str, t_token **tokens);
static int	get_word(char **str, char **word);
static void	give_token_types(t_token **tokens);

t_token	*tokenize(char *str)
{
	t_token		*tokens;
	char		*start;

	tokens = NULL;
	start = str;
	while (*str != '\0')
	{
		if (create_token(&str, &tokens) == FAIL)
		{
			clean_tokens(&tokens);
			free(start);
			return (NULL);
		}
	}
	give_token_types(&tokens);
	free(start);
	return (tokens);
}

static int	create_token(char **str, t_token **tokens)
{
	t_token			*token;
	char			*word;

	if (get_word(str, &word) == FAIL)
		return (FAIL);
	token = token_new(word, E_NONE);
	if (token == NULL)
		return (FAIL);
	token_add_back(tokens, token);
	return (SUCCESS);
}

static int	get_word(char **str, char **word)
{
	size_t	len;

	skip_spaces(str);
	len = next_word_length(*str);
	*word = malloc(sizeof(char) * (len + 1));
	if (*word == NULL)
		return (FAIL);
	ft_strlcpy(*word, *str, len + 1);
	*str += len;
	return (SUCCESS);
}

static void	give_token_types(t_token **tokens)
{
	t_token	*current;
	t_token	*previous;

	current = *tokens;
	while (current != NULL && current->type == E_NONE)
	{
		previous = prev_token(*tokens, current);
		current->type = E_ARGUMENT;
		if (previous != NULL && previous->type == E_REDIRECTION)
			current->type = E_FILENAME;
		else if (is_redirect(current->token))
			current->type = E_REDIRECTION;
		else if (ft_strcmp(current->token, "|") == 0)
			current->type = E_PIPE;
		else if (current == *tokens && !is_redirect(current->token))
			current->type = E_COMMAND;
		else if ((previous != NULL && previous->type == E_FILENAME)
			&& !is_redirect(current->token))
			current->type = E_COMMAND;
		else if (previous != NULL && previous->type == E_PIPE)
			current->type = E_COMMAND;
		else if (is_option(current->token))
			current->type = E_OPTION;
		current = current->next;
	}
}
