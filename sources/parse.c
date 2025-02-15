/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmattos- <nmattos-@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/02 10:55:22 by nmattos-      #+#    #+#                 */
/*   Updated: 2025/02/15 11:43:43 by nmattos       ########   odam.nl         */
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

static bool	replace_var(char **str, char *var_ptr, t_variable *vars)
{
	t_variable	*var;
	char		*to_replace;
	bool		ret_value;
	int			i;

	to_replace = var_ptr;
	i = 1;
	ret_value = false;
	while (valid_char(to_replace[i]))
		i++;
	to_replace = ft_strndup(to_replace, i);
	if (to_replace == NULL)
	{
		free(*str);
		return (ret_value);
	}
	to_replace[0] = '$';
	var = var_find(vars, to_replace + 1);
	if (var && var->value)
	{
		*str = ft_strreplace(*str, to_replace, var->value, var_ptr);
		ret_value = true;
	}
	free(to_replace);
	return (ret_value);
}

static int	replace_custom_variable(t_variable *vars, char **arg)
{
	char	*var_ptr;
	int		nth_var;
	bool	is_replaced;

	var_ptr = ft_strchr(*arg, '$');
	nth_var = 0;
	while (var_ptr)
	{
		if (char_is_escaped(*arg, var_ptr) == false
			&& in_single_quotes(*arg, var_ptr) == false)
		{
			is_replaced = replace_var(arg, var_ptr, vars);
			if (*arg == NULL)
				return (FAIL);
			if (is_replaced == false)
				nth_var++;
		}
		else
			nth_var++;
		var_ptr = get_nth_var(*arg, nth_var);
	}
	return (SUCCESS);
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

	command_index = *i;
	if (parse_command(split_input, commands, i) == FAIL)
		return (clean_all(variables, commands, split_input), FAIL);
	if (parse_redirect(split_input, commands, i, command_index) == FAIL)
		return (clean_all(variables, commands, split_input), FAIL);
	if (cmd_last(*commands)->in_type == STRING
		|| cmd_last(*commands)->pattern != NULL)
	{
		if (split_input[*i] != NULL)
		{
			if (replace_custom_variable(*variables, \
					&cmd_last(*commands)->pattern) == FAIL)
				return (clean_all(variables, commands, split_input), FAIL);
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
	split_input = parse_split(input);
	if (split_input == NULL)
		return (NULL);
	// printf("-----------------------\n");
	// while (split_input[i] != NULL)
	// {
	// 	printf("split_input[%d]: %s\n", i, split_input[i]);
	// 	i++;
	// }
	// printf("-----------------------\n");
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
	// printf("-----------------------\n");
	// printf("\ncommands->command: %s\n", commands->command);
	// printf("options: %s\n", commands->options);
	// printf("pattern: %s\n\n", commands->pattern);
	// printf("-----------------------\n");
	return (commands);
}
