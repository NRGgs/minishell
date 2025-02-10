/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:56:52 by iriadyns          #+#    #+#             */
/*   Updated: 2025/02/10 14:52:48 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exit_shell(char *pattern, t_command **cmd_list, t_env **env_list)
{
	int	exit_code;

	if (!pattern)
		exit_code = g_exit_status;
	else
		exit_code = ft_atoi(pattern, 0);
	if (cmd_list && *cmd_list)
		clean_commands(cmd_list);
	rl_clear_history();
	clear_history();
	if (env_list && *env_list)
		clear_env_list(*env_list);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(exit_code);
}
