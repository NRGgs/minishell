/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:55:22 by nmattos-          #+#    #+#             */
/*   Updated: 2024/12/02 16:53:25 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"

t_command	*parse_user_input(char *input)
{
	t_command	*commands;
	t_variable	*variables;
	char		**split_input;
	int			i;

	// tokenize user input
	split_input = ft_split(input, ' ');
	i = 0;
	while (split_input[i] != NULL)
	{
		// check token for variable, if variable, parse and add to *variables
		if (is_variable(split_input[i]))
		{
			parse_variable(split_input[i], &variables);
		}
		// check token for command
		else if (is_command(split_input[i]))
		{
			// if command, parse and add to *commands
				// add options '-' to *commands
			// if HERE_DOC (<<), readlines until EOF
			// if TEXTFILE (<), set *input/*output to filename
			// if PIPE (|), set in/out accordingly
		}
		i++;
	}
	return (commands);
}
