/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmattos- <nmattos-@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/02 10:55:22 by nmattos-      #+#    #+#                 */
/*   Updated: 2024/12/04 13:11:34 by nmattos       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"

static void	clean_all(t_variable **vars, t_command **cmds, char **split_input)
{
	clean_2d_array(split_input);
	clean_variables(vars);
	clean_commands(cmds);
}

t_command	*parse_user_input(char *input)
{
	t_command	*commands;
	t_variable	*variables;
	char		**split_input;
	int			i;
	int			command_index;

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
				clean_all(&variables, &commands, split_input);
				return (NULL);
			}
		}
		// check token for command
		else if (is_command(split_input[i]))
		{
			command_index = i;
			// if command, parse and add to *commands (including options)
			if (parse_command(split_input, &commands, &i) == FAIL)
			{
				clean_all(&variables, &commands, split_input);
				return (NULL);
			}
			// if REDIRECT (>, <), set *input/*output to filename
			// if HERE_DOC (<<), readlines until EOF
			// if PIPE (|), set in/out accordingly
			if (parse_redirect(split_input, &commands, &i, command_index) == FAIL)
			{
				clean_all(&variables, &commands, split_input);
				return (NULL);
			}
			if (cmd_last(commands)->in_type == STRING)
			{
				if (split_input[i] != NULL
					&& split_input[i - 1][ft_strlen(split_input[i - 1]) - 1] == '\"')
				{
					char *temp = replace_variable(cmd_last(commands)->input, variables);
					if (temp == NULL)
					{
						clean_all(&variables, &commands, split_input);
						return (NULL);
					}
					cmd_last(commands)->input = temp;
				}
			}
		}
		i++;
	}
	clean_2d_array(split_input);
	clean_variables(&variables);
	return (commands);
}

int	main(void)
{
	char *s = "NAME=\"Noah\" echo \"This is $NAME epic sauce!!\" | wc -w > output.txt";
	printf("%s\n\n", s);
	t_command *cmds = parse_user_input(s);
	if (cmds == NULL)
	{
		printf("Error parsing user input\n");
		return (1);
	}
	printf("Parsed user input successfully\n\n");

	printf("cmds->command: %s\n", cmds->command);
	printf("cmds->options: %s\n", cmds->options);
	printf("cmds->in_type: %d\n", cmds->in_type);
	printf("cmds->out_type: %d\n", cmds->out_type);
	printf("cmds->input: %s\n", cmds->input);
	printf("cmds->output: %s\n", cmds->output);
	printf("\n");
	t_command *temp = cmds;
	cmds = cmds->next;
	printf("cmds->command: %s\n", cmds->command);
	printf("cmds->options: %s\n", cmds->options);
	printf("cmds->in_type: %d\n", cmds->in_type);
	printf("cmds->out_type: %d\n", cmds->out_type);
	printf("cmds->input: %s\n", cmds->input);
	printf("cmds->output: %s\n", cmds->output);
	clean_commands(&temp);
	return (0);
}
