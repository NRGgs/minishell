/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:17:48 by iriadyns          #+#    #+#             */
/*   Updated: 2025/01/06 09:45:34 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(char *command)
{
	if (!command)
		return (0);
	if (!ft_strncmp(command, "cd", 3))
		return (1);
	if (!ft_strncmp(command, "echo", 5))
		return (1);
	if (!ft_strncmp(command, "pwd", 4))
		return (1);
	if (!ft_strncmp(command, "env", 4))
		return (1);
	if (!ft_strncmp(command, "export", 7))
		return (1);
	if (!ft_strncmp(command, "unset", 6))
		return (1);
	if (!ft_strncmp(command, "exit", 5))
		return (1);
	return (0);
}

int	handle_cd(t_command *command)
{
	if (command->input)
		return (cd(command->env_list, &command->input));
	return (cd_home(command->env_list));
}

int	execute_builtin(t_command *command)
{
	if (!command || !command->command)
	{
		ft_putstr_fd("Error: Invalid command structure.\n", 2);
		return (1);
	}
	if (ft_strncmp(command->command, "cd", 3) == 0)
		return (handle_cd(command));
	else if (ft_strncmp(command->command, "echo", 5) == 0)
		return (echo(&command->input));
	else if (ft_strncmp(command->command, "pwd", 4) == 0)
		return (pwd(&command->input));
	else if (ft_strncmp(command->command, "env", 4) == 0)
		return (env());
	else if (ft_strncmp(command->command, "export", 7) == 0)
		return (my_export(&command->env_list, command->input));
	else if (ft_strncmp(command->command, "unset", 6) == 0)
		return (unset(command->env_list, command->input));
	else if (ft_strncmp(command->command, "exit", 5) == 0)
		return (exit_shell(command->input));
	ft_putstr_fd("Error: Unknown built-in command.\n", 2);
	return (1);
}
