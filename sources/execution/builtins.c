/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:17:48 by iriadyns          #+#    #+#             */
/*   Updated: 2024/12/10 12:08:40 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int is_builtin(char *command)
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

int execute_builtin(t_command *command)
{
	if (!command || !command->command)
	{
		ft_putstr_fd("Error: Invalid command structure.\n", 2);
		return (1);
	}
	if (ft_strncmp(command->command, "cd", 3) == 0)
	{
		if (command->input)
			return cd(command->env_list, command->input);
		else
			return cd_home(command->env_list);
	}
	else if (ft_strncmp(command->command, "echo", 5) == 0)
		return (echo(command->input));
	else if (ft_strncmp(command->command, "pwd", 4) == 0)
		return (pwd(command->input));
	else if (ft_strncmp(command->command, "env", 4) == 0)
		return (env());
	else if (ft_strncmp(command->command, "export", 7) == 0)
		return (my_export(command->env_list, command->input));
	else if (ft_strncmp(command->command, "unset", 6) == 0)
		return (unset(command->env_list, command->input));
	else if (ft_strncmp(command->command, "exit", 5) == 0)
		return (exit_shell(command->input));

	ft_putstr_fd("Error: Unknown built-in command.\n", 2);
	return (1);
}
