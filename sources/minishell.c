/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmattos- <nmattos-@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/08 10:48:10 by nmattos       #+#    #+#                 */
/*   Updated: 2025/02/13 15:40:19 by nmattos       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_status = 0;

/*	Sets the error message and the exit status.
 *
 *	error_msg: the error message to be printed.
 *	error_code: the exit status to be set.
 *
 * 	Returns: none.
 */
void	set_error(char *error_msg, int error_code)
{
	perror(error_msg);
	g_exit_status = error_code;
}

/*	Reads the user input and returns it as a string.
 *
 *	Returns: the user input as a string.
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

/*	Parses the user's input, and runs them as commands.
 *
 *	my_env_list: the environment variables list.
 *
 *	Returns: none.
 */
// void	run_commands(t_env *my_env_list)
// {
// 	char		*input;
// 	t_command	*commands;
// 	t_command	*tmp;

// 	while (1)
// 	{
// 		input = read_input();
// 		if (input == NULL)
// 			return ;
// 		add_history(input);
// 		commands = parse_user_input(input);
// 		free(input);
// 		if (commands == NULL)
// 			continue ;
// 		tmp = commands;
// 		while (tmp)
// 		{
// 			tmp->env_list = my_env_list;
// 			tmp = tmp->next;
// 		}
// 		printf("commands->command: %s\n", commands->command);
// 		printf("pattern: %s\n", commands->pattern);
// 		printf("input: %s\n", commands->input);
// 		printf("output: %s\n", commands->output);
// 		execute_commands(commands);
// 		clean_commands(&commands);
// 	}
// }
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
