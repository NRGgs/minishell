/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_without_pipe_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:53:50 by iriadyns          #+#    #+#             */
/*   Updated: 2025/02/10 19:19:48 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
