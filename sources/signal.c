/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:38:36 by nmattos-          #+#    #+#             */
/*   Updated: 2025/02/24 11:05:25 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	signal_handler(int signum);

/**
 * @brief Catch signals and deal with them accordingly.
 * @param None
 */
void	check_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * @brief Handle CTRL-C signal.
 * @param signum The signal number received.
 */
static void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_status = SIGINT_CANCELLATION;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/**
 * @brief Handle CTRL-C for heredoc.
 * @param signum The signal number received.
 * Redirects input to /dev/null to force an EOF.
 */
void	signal_heredoc(int signum)
{
	int	dev_null_fd;

	if (signum == SIGINT)
	{
		g_exit_status = SIGINT_CANCELLATION;
		dev_null_fd = open("/dev/null", O_RDONLY);
		dup2(dev_null_fd, STDIN_FILENO);
		close(dev_null_fd);
	}
}

/**
 * @param error_msg The error message to be printed.
 * @param error_code The exit status to be set.
 */
void	set_error(char *error_msg, int error_code)
{
	perror(error_msg);
	g_exit_status = error_code;
}
