/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:56:52 by iriadyns          #+#    #+#             */
/*   Updated: 2025/02/11 12:59:48 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exit_shell(char *pattern)
{
	int	exit_code;

	if (!pattern)
		exit_code = g_exit_status;
	else
		exit_code = ft_atoi(pattern, 0);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	g_exit_status = exit_code;
	return (SHELL_EXIT);
}
