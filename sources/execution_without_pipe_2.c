/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_without_pipe_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:53:50 by iriadyns          #+#    #+#             */
/*   Updated: 2025/02/17 14:15:14 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Executes commands when there is no pipe.
 * Chooses between built-in and external command execution.
 *
 * @param commands The command structure.
 *
 * @return The shell exit status.
 */
int	execution_without_pipe(t_command *commands)
{
	if (!commands || !commands->command)
	{
		ft_putstr_fd("Error: Invalid command structure.\n", 2);
		return (SHELL_CONTINUE);
	}
	if (is_builtin(commands->command))
		return (exec_builtin_no_pipe(commands));
	return (exec_external_no_pipe(commands));
}
