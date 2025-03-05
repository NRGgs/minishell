/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:40:41 by nmattos           #+#    #+#             */
/*   Updated: 2025/03/05 11:49:07 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	check_open_quotes(char *str, size_t i);
static void	update_escape(bool *escaped, char c);

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
	print_commands(commands);					// Debugging
	print_tokens(tokens);						// Debugging
	clean_tokens(&tokens);
	return (commands);
}

static char	check_open_quotes(char *str, size_t i)
{
	bool	in_single;
	bool	in_double;
	bool	escaped;

	in_single = false;
	in_double = false;
	escaped = false;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && !in_double && escaped == false)
			in_single = !in_single;
		else if (str[i] == '\"' && !in_single && escaped == false)
			in_double = !in_double;
		else if (!in_single)
			update_escape(&escaped, str[i]);
		i++;
	}
	if (in_single)
		return ('\'');
	if (in_double)
		return ('\"');
	return ('0');
}

static void	update_escape(bool *escaped, char c)
{
	if (c == '\\')
		*escaped = !*escaped;
	if (c != '\\')
		*escaped = false;
}
