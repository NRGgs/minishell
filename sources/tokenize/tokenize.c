/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:37:47 by nmattos           #+#    #+#             */
/*   Updated: 2025/03/10 15:25:39 by nmattos-         ###   ########.fr       */
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
	t_token	*curr;
	t_token	*prev;

	curr = *tokens;
	while (curr && curr->type == E_NONE)
	{
		prev = prev_token(*tokens, curr);
		curr->type = E_ARGUMENT;
		if (prev && prev->type == E_REDIRECTION)
			curr->type = E_FILENAME;
		else if (is_redirect(curr->token))
			curr->type = E_REDIRECTION;
		else if (ft_strcmp(curr->token, "|") == 0)
			curr->type = E_PIPE;
		else if (curr == *tokens && !is_redirect(curr->token))
			curr->type = E_COMMAND;
		else if ((prev && (prev->type == E_COMMAND || prev->type == E_OPTION))
			&& is_option(curr->token))
			curr->type = E_OPTION;
		else if (prev && (prev->type == E_PIPE || prev->type == E_FILENAME))
			curr->type = E_COMMAND;
		curr = curr->next;
	}
}
