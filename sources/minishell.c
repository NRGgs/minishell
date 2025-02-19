/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 10:48:10 by nmattos           #+#    #+#             */
/*   Updated: 2025/02/19 13:42:30 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_status = 0;

/**
 * @param error_msg The error message to be printed.
 * @param error_code The exit status to be set.
 *
 * @return None.
 */
void	set_error(char *error_msg, int error_code)
{
	perror(error_msg);
	g_exit_status = error_code;
}

/**
 * Reads the user input and returns it as a string.
 *
 * @param prompt The prompt message to display to the user.
 * @return The user input as a string.
 */
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
		ft_strlcat(dir, " $ ", 1024);
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

static void	print_command(t_command *cmd)
{
	printf("Command: %s\n", (cmd->command) ? cmd->command : "NULL");
	printf("Options: %s\n", (cmd->options) ? cmd->options : "NULL");
	printf("Pattern: %s\n", (cmd->pattern) ? cmd->pattern : "NULL");
	printf("Input Type: %d\n", cmd->in_type);
	printf("Output Type: %d\n", cmd->out_type);
	printf("Input: %s\n", (cmd->input) ? cmd->input : "NULL");
	printf("Output: %s\n", (cmd->output) ? cmd->output : "NULL");
	printf("Environment List:\n");
	printf("-----\n");
}
static void	print_commands(t_command *commands)
{
	while (commands)
	{
		print_command(commands);
		commands = commands->next;
	}
}
static int	parse_and_exec(char *input, t_env *env_list)
{
	t_command	*commands;
	t_command	*tmp;
	int			ret;

	commands = parse_user_input(input);
	if (!commands)
		return (SHELL_CONTINUE);
	tmp = commands;
	while (tmp)
	{
		tmp->env_list = env_list;
		tmp = tmp->next;
	}
	print_commands(commands);
	ret = execute_commands(commands);
	clean_commands(&commands);
	return (ret);
}

void	run_commands(t_env *my_env_list)
{
	char	*input;
	int		ret;

	while (1)
	{
		input = read_input();
		if (!input)
			return ;
		add_history(input);
		ret = parse_and_exec(input, my_env_list);
		if (ret == SHELL_EXIT)
			return ;
	}
}

int	main(void)
{
	t_env		*my_env_list;

	my_env_list = init_env_list();
	check_signals();
	run_commands(my_env_list);
	clear_history();
	rl_clear_history();
	clear_env_list(my_env_list);
	return (g_exit_status);
}
