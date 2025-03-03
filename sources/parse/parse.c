/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:40:41 by nmattos           #+#    #+#             */
/*   Updated: 2025/03/03 16:32:59 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	check_open_quotes(char *str, size_t i);

void	print_commands(t_command *commands)
{
	while (commands)
	{
		printf("Command: %s\n", commands->command);
		printf("Pattern: %s\n", commands->pattern);
		printf("input: %s\n", commands->input);
		printf("output: %s\n", commands->output);
		commands = commands->next;
	}
}

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Token: %s\n", tokens->token);
		printf("Type: %d\n", tokens->type);
		tokens = tokens->next;
	}
}

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
	print_commands(commands);
	print_tokens(tokens);
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
			if (str[i] == '\0')
				return (quote);
		}
		i++;
	}
	return ('0');
}
