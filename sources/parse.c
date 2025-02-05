/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:55:22 by nmattos-          #+#    #+#             */
/*   Updated: 2025/02/05 12:33:07 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*	Clean all allocated memory.
 *
 *	vars:			the variables to be cleaned.
 *	cmds:			the commands to be cleaned.
 *	split_input:	the split input to be cleaned.
 *
 *	Return: none.
 */
static void	clean_all(t_variable **vars, t_command **cmds, char **split_input)
{
	if (vars != NULL)
		clean_variables(vars);
	if (cmds != NULL)
		clean_commands(cmds);
	if (split_input != NULL)
		clean_2d_array(split_input);
}

/*	Parse the command given by the user.
 *
 *	split_input:	the split user input.
 *	commands:		the linked list of commands.
 *	variables:		the linked list of variables.
 *	i:				the index of the current token.
 *
 *	Return: SUCCESS (1) / FAIL (0).
*/
int	parse_full_command(\
	char **split_input, \
	t_command **commands, \
	t_variable **variables, \
	int *i)
{
	int		command_index;
	char	*temp;

	command_index = *i;
	if (parse_command(split_input, commands, i) == FAIL)
		return (clean_all(variables, commands, split_input), FAIL);
	if (parse_redirect(split_input, commands, i, command_index) == FAIL)
		return (clean_all(variables, commands, split_input), FAIL);
	if (cmd_last(*commands)->in_type == STRING
		|| cmd_last(*commands)->pattern != NULL)
	{
		if (split_input[*i] != NULL
			&& (split_input[*i][ft_strlen(split_input[*i]) - 1] == '\"'
			|| split_input[*i][ft_strlen(split_input[*i]) - 1] == '\''))
		{
			temp = replace_variable(cmd_last(*commands)->pattern, *variables);
			if (temp == NULL)
			{
				clean_all(variables, commands, split_input);
				return (FAIL);
			}
			cmd_last(*commands)->pattern = temp;
		}
	}
	return (SUCCESS);
}

/*	Parse the user input.
 *
 *	input:	the user input.
 *
 *	Return: the linked list of commands.
 */
t_command	*parse_user_input(char *input)
{
	t_command	*commands;
	t_variable	*variables;
	char		**split_input;
	int			i;

	commands = NULL;
	variables = NULL;
	split_input = ft_split(input, ' ');
	if (split_input == NULL)
		return (NULL);
	i = 0;
	while (split_input[i] != NULL)
	{
		if (is_variable(split_input[i]))
		{
			if (!parse_variable(split_input[i], &variables))
				return (clean_all(&variables, &commands, split_input), NULL);
		}
		else
			if (!parse_full_command(split_input, &commands, &variables, &i))
				return (clean_all(&variables, &commands, split_input), NULL);
		i++;
	}
	clean_all(&variables, NULL, split_input);
	return (commands);
}
