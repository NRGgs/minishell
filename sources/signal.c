/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:38:36 by nmattos-          #+#    #+#             */
/*   Updated: 2025/02/18 11:05:50 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	signal_handler(int signum);

/*	Catch signals and deal with them accordingly.
 *
 *	SIGINT:		CTRL+C
 *	SIGQUIT:	CTRL+\
 */
void	check_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

/*	Handle CTRL-C signal.
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

/*	Handle CTRL-C for heredoc.
 *	Redirects input to /dev/null to force an EOF.
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
