/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:56:52 by iriadyns          #+#    #+#             */
/*   Updated: 2025/02/10 18:50:03 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exit_shell(char *pattern, t_command **cmd_list)
{
	int	exit_code;

	if (!pattern)
		exit_code = g_exit_status;
	else
		exit_code = ft_atoi(pattern, 0);
	if (cmd_list && *cmd_list)
		clean_commands(cmd_list);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	g_exit_status = exit_code;
	return (SHELL_EXIT);
}
