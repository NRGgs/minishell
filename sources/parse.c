/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:55:22 by nmattos-          #+#    #+#             */
/*   Updated: 2025/01/23 13:58:23 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	clean_all(t_variable **vars, t_command **cmds, char **split_input)
{
	if (vars != NULL)
		clean_variables(vars);
	if (cmds != NULL)
		clean_commands(cmds);
	if (split_input != NULL)
		clean_2d_array(split_input);
}

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
	if (cmd_last(*commands)->in_type == STRING)
	{
		if (split_input[*i] != NULL
			&& split_input[*i - 1][ft_strlen(split_input[*i - 1]) - 1] == '\"')
		{
			temp = replace_variable(cmd_last(*commands)->input, *variables);
			if (temp == NULL)
			{
				clean_all(variables, commands, split_input);
				return (FAIL);
			}
			cmd_last(*commands)->input = temp;
		}
	}
	return (SUCCESS);
}

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
