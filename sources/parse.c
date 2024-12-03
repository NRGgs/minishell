/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmattos- <nmattos-@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/02 10:55:22 by nmattos-      #+#    #+#                 */
/*   Updated: 2024/12/03 13:48:41 by nmattos       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"

static void	clean_all(t_variable **vars, t_command **cmds)
{
	clean_variables(vars);
	clean_commands(cmds);
}

t_command	*parse_user_input(char *input)
{
	t_command	*commands;
	t_variable	*variables;
	char		**split_input;
	int			i;

	commands = NULL;
	variables = NULL;
	// tokenize user input
	split_input = ft_split(input, ' ');
	if (split_input == NULL)
		return (NULL);
	i = 0;
	while (split_input[i] != NULL)
	{
		// check token for variable, if variable, parse and add to *variables
		if (is_variable(split_input[i]))
		{
			if (parse_variable(split_input[i], &variables) == FAIL)
			{
				clean_all(&variables, &commands);
				return (NULL);
			}
		}
		// check token for command
		else if (is_command(split_input[i]))
		{
			// if command, parse and add to *commands (including options)
			if (parse_command(split_input, &commands, &i) == FAIL)
			{
				clean_all(&variables, &commands);
				return (NULL);
			}
			// if HERE_DOC (<<), readlines until EOF
			// if TEXTFILE (<), set *input/*output to filename
			// if PIPE (|), set in/out accordingly
		}
		i++;
	}
	clean_variables(&variables);
	return (commands);
}
