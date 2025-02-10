/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:38:36 by nmattos-          #+#    #+#             */
/*   Updated: 2025/02/10 13:18:57 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	signal_handler(int signum);
static void	signal_handler_heredoc(int signum);

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

/*	Catch signals and deal with them accordingly (HEREDOC).
 *
 *	SIGINT:		CTRL+C
 *	SIGQUIT:	CTRL+\
 */
void	check_signals_heredoc(void)
{
	signal(SIGINT, signal_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

/*	Handle incoming signals.
 */
static void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/*	Handle incoming signals.
 */
static void	signal_handler_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
