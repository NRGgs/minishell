/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmattos <nmattos@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/25 15:40:41 by nmattos       #+#    #+#                 */
/*   Updated: 2025/02/25 15:52:07 by nmattos       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	check_open_quotes(char *str, size_t i);

t_command	*parse_input(char *input)
{
	t_token		*tokens;
	t_command	*commands;
	char		quote;

	if (input == NULL)
		return (NULL);
	quote = check_open_quotes(input, 0);
	if (quote != '0')
	{
		input = read_till_quotes(quote, &input);
		if (input == NULL)
			return (NULL);
	}
	tokens = tokenize(input);
	if (tokens == NULL)
		return (NULL);
	commands = get_commands(tokens);
	clean_tokens(&tokens);
	return (commands);
}

static char	check_open_quotes(char *str, size_t i)
{
	char	quote;
	bool	escaped;

	quote = '0';
	escaped = false;
	while (str[i] != '\0')
	{
		escaped = skip_escapes(str, &i, escaped);
		if ((str[i] == '\'' || str[i] == '\"') && !escaped)
		{
			quote = str[i++];
			while (str[i] != '\0' && str[i] != quote)
				i++;
			if (str[i] == '\0')
				return (quote);
		}
		i++;
	}
	return ('0');
}
