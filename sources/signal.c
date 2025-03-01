/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmattos- <nmattos-@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/10 11:38:36 by nmattos-      #+#    #+#                 */
/*   Updated: 2025/03/01 16:55:05 by nmattos       ########   odam.nl         */
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
		dev_null_fd = open("/dev/null", O_RDONLY);
		dup2(dev_null_fd, STDIN_FILENO);
		close(dev_null_fd);
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

/**
 * @param error_msg The error message to be printed.
 * @param error_code The exit status to be set.
 */
void	set_error(char *error_msg, int error_code)
{
	errno = error_code;
	if (error_code == CMD_NOT_FOUND)
		errno = ENOENT;
	else if (error_code == SIGINT_CANCELLATION)
		errno = EINTR;
	else if (error_code == ILLEGAL_INSTRUCTION
		|| error_code == FAILED_ASSERTION)
		errno = EINVAL;
	else if (error_code == ILLEGAL_DIVISION)
		errno = EDOM;
	else if (error_code == INT_OVERFLOW)
		errno = ERANGE;
	else if (error_code == MEMORY_OVERFLOW)
		errno = ENOMEM;
	else if (error_code == UNALIGNED_MEM_ACCESS
		|| error_code == SEG_FAULT)
		errno = EFAULT;
	else
		errno = EIO;
	perror(error_msg);
}
