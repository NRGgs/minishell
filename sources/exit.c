/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:56:52 by iriadyns          #+#    #+#             */
/*   Updated: 2025/02/12 13:03:51 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
