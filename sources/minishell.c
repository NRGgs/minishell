/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 10:48:10 by nmattos           #+#    #+#             */
/*   Updated: 2025/02/24 12:40:44 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_status = 0;

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
	if (getcwd(dir, sizeof(dir)) == NULL)
	{
		set_error("getenv() error", MINOR);
		return (NULL);
	}
	ft_strlcat(dir, " $ ", 1024);
	prompt = ft_strjoin(username, ft_strrchr(dir, '/'));
	input = readline(prompt);
	free(prompt);
	if (input == NULL)
		printf("exit\n");
	return (input);
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
	ret = execute_commands(commands);
	clean_commands(&commands);
	return (ret);
}

static void	run_commands(t_env *my_env_list)
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

static void	noninteractive_mode(t_env *my_env_list, int argc, char *argv[])
{
	char	*input;

	if (argc == 1)
		return ;
	if (ft_strcmp(argv[1], "-c") != 0 || argc == 2)
	{
		if (ft_strcmp(argv[1], "-c") != 0)
			set_error("Invalid option", MAJOR);
		else
			set_error("-c: option requires an argument", MAJOR);
		clear_env_list(my_env_list);
		exit(g_exit_status);
	}
	input = ft_strdup(argv[2]);
	if (!input)
	{
		clear_env_list(my_env_list);
		set_error("memory allocation error", MAJOR);
		exit(g_exit_status);
	}
	parse_and_exec(input, my_env_list);
	clear_env_list(my_env_list);
	exit(g_exit_status);
}

int	main(int argc, char *argv[])
{
	t_env		*my_env_list;

	my_env_list = init_env_list();
	noninteractive_mode(my_env_list, argc, argv);
	check_signals();
	run_commands(my_env_list);
	clear_history();
	rl_clear_history();
	clear_env_list(my_env_list);
	return (g_exit_status);
}
