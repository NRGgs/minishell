/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 10:48:10 by nmattos           #+#    #+#             */
/*   Updated: 2025/01/26 16:24:09 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_status = -1;

// Test function (TEMP)
void	print_commands(t_command *commands)
{
	t_command	*tmp;

	tmp = commands;
	while (tmp != NULL)
	{
		printf("\ncommands->command: %s\n", tmp->command);
		printf("commands->options: %s\n", tmp->options);
		printf("commands->in_type: %d\n", tmp->in_type);
		printf("commands->out_type: %d\n", tmp->out_type);
		printf("commands->input: %s\n", tmp->input);
		printf("commands->output: %s\n", tmp->output);
		printf("commands->pattern: %s\n\n", tmp->pattern);
		tmp = tmp->next;
	}
}

void	set_error(char *error_msg, int error_code)
{
	perror(error_msg);
	g_exit_status = error_code;
}

char	*read_input(void)
{
	char	*input;
	char	*username;
	char	dir[1024];
	char	*prompt;

	username = getenv("USER");
	if (username == NULL)
	{
		set_error("getenv() error", MINOR);
		return (NULL);
	}
	if (getcwd(dir, sizeof(dir)) != NULL)
	{
		strcat(dir, " $ ");
		prompt = ft_strjoin(username, ft_strrchr(dir, '/'));
	}
	else
	{
		set_error("getenv() error", MINOR);
		return (NULL);
	}
	input = readline(prompt);
	free(prompt);
	return (input);
}

int	main(void)
{
	char		*input;
	t_command	*commands;
	t_env		*my_env_list;

	my_env_list = init_env_list();
	check_signals();
	while (1)
	{
		input = read_input();
		if (input == NULL)
			break ;
		add_history(input);
		commands = parse_user_input(input);
		if (commands == NULL)
		{
			free(input);
			continue ;
		}
		t_command *tmp = commands;
		while (tmp)
		{
			tmp->env_list = my_env_list;
			tmp = tmp->next;
		}
		print_commands(commands);// Test function (TEMP)
		execute_commands(commands);
		free(input);
		clean_commands(&commands);
	}
	clear_history();
	rl_clear_history();
	return (g_exit_status);
}
