/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 10:48:10 by nmattos           #+#    #+#             */
/*   Updated: 2024/12/10 11:34:26 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"

// Test function (TEMP)
void	print_commands(t_command *commands)
{
	t_command	*tmp;

	tmp = commands;
	while (tmp != NULL)
	{
		printf("commands->command: %s\n", tmp->command);
		printf("commands->options: %s\n", tmp->options);
		printf("commands->in_type: %d\n", tmp->in_type);
		printf("commands->out_type: %d\n", tmp->out_type);
		printf("commands->input: %s\n", tmp->input);
		printf("commands->output: %s\n", tmp->output);
		tmp = tmp->next;
	}
}

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
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
		perror("getenv() error");
		return (NULL);
	}
	if (getcwd(dir, sizeof(dir)) != NULL) {
		strcat(dir, " $ ");
		prompt = ft_strjoin(username, ft_strrchr(dir, '/'));
	} else {
		perror("getcwd() error");
		return (NULL);
	}
	input = readline(prompt);
	free(prompt);
	return (input);
}
int	main(void)
{
	char *input;
	t_command *commands;

	signal(SIGINT, signal_handler);		// CTRL + C
	signal(SIGQUIT, SIG_IGN);			// CTRL + \'
	while (1)
	{
		input = read_input();
		if (input == NULL)				// CTRL + D
			break ;

		add_history(input);
		commands = parse_user_input(input);
		if (commands == NULL) {
			free(input);
			continue;
		}
		// execute commands

		free(input);
		print_commands(commands);		// Test function (TEMP)
		clean_commands(&commands);
	}
	clear_history();
	rl_clear_history();
	return (0);
}
