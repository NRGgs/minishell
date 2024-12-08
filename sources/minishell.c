/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmattos <nmattos@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/08 10:48:10 by nmattos       #+#    #+#                 */
/*   Updated: 2024/12/08 12:16:39 by nmattos       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"

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
	char	prompt[1024];

	if (getcwd(prompt, sizeof(prompt)) != NULL) {
        strcat(prompt, "$ ");
    } else {
        perror("getcwd() error");
        exit(EXIT_FAILURE);
    }
	input = readline(prompt);
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
        print_commands(commands);
        clean_commands(&commands);
    }
    clear_history();
	rl_clear_history();
    return (0);
}
