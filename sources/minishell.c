/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: iriadyns <iriadyns@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/08 10:48:10 by nmattos       #+#    #+#                 */
/*   Updated: 2025/04/05 10:27:56 by nmattos       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile int g_signal;

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
	check_signals();
	input = readline(prompt);
	free(prompt);
	if (input == NULL)
		printf("exit\n");
	return (input);
}

static int	parse_and_exec(char *input, t_env *env_list, t_shell *shell)
{
	t_command	*commands;
	t_command	*tmp;
	int			ret;

	commands = parse_input(input);
	if (!commands)
		return (SHELL_CONTINUE);
	tmp = commands;
	while (tmp)
	{
		tmp->env_list = env_list;
		tmp = tmp->next;
	}
	signal(SIGINT, command_handler);
	signal(SIGQUIT, command_handler);
	ret = execute_commands(commands, shell);
	clean_commands(&commands);
	return (ret);
}

static void	run_commands(t_shell *shell)
{
	char	*input;
	int		ret;

	while (1)
	{
		g_signal = 0;
		input = read_input();
		if (!input)
			return ;
		if (is_all_whitespace(input))
		{
			free(input);
			continue ;
		}
		if (ft_strlen(input) > 0)
			add_history(input);
		ret = parse_and_exec(input, shell->env_list, shell);
		if (ret == SHELL_EXIT)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			return ;
		}
		if (g_signal == 130)
			shell->exit_status = 130;
	}
}

static void	noninteractive_mode(t_shell *shell, int argc, char *argv[])
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
		clear_env_list(shell->env_list);
		exit(shell->exit_status);
	}
	input = ft_strdup(argv[2]);
	if (!input)
	{
		clear_env_list(shell->env_list);
		set_error("memory allocation error", MAJOR);
		exit(shell->exit_status);
	}
	parse_and_exec(input, shell->env_list, shell);
	clear_env_list(shell->env_list);
	exit(shell->exit_status);
}

int	main(int argc, char *argv[])
{
	t_shell	shell;

	shell.exit_status = 0;
	shell.env_list = init_env_list();
	noninteractive_mode(&shell, argc, argv);
	run_commands(&shell);
	clear_history();
	rl_clear_history();
	clear_env_list(shell.env_list);
	return (shell.exit_status);
}
