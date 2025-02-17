/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:56:52 by iriadyns          #+#    #+#             */
/*   Updated: 2025/02/17 14:44:40 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Handles the exit built-in command.
 * if a numeric argument is provided, it is used as the exit code;
 * otherwise, the current g_exit_status is used.
 *
 * @param pattern The exit argument.
 *
 * @return SHELL_EXIT
 */
int	exit_shell(char *pattern)
{
	int	exit_code;
	int	error;

	if (!pattern)
		exit_code = g_exit_status;
	else
	{
		exit_code = ft_atoi(pattern, &error);
		if (error)
		{
			ft_putstr_fd("exit: ", STDERR_FILENO);
			ft_putstr_fd(pattern, STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			g_exit_status = MAJOR;
			return (SHELL_EXIT);
		}
	}
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	g_exit_status = exit_code;
	return (SHELL_EXIT);
}
