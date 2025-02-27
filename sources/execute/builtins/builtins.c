/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:06:42 by iriadyns          #+#    #+#             */
/*   Updated: 2025/02/27 15:31:32 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * @brief Checks if the given command is a built-in command.
 * Compares the command string against a known list of built-ins.
 *
 * @param command The command string.
 *
 * @return 1 if it is a built-in command, 0 otherwise.
 */
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

/**
 * @brief Handles the 'cd' built-in command.
 * Changes the current directory. If no argument is provided,
 * it changes to HOME.
 *
 * @param command The command structure.
 *
 * @return 0 on success, non-zero on failure.
 */
int	handle_cd(t_command *command, t_shell *shell)
{
	if (command->pattern)
		return (cd(command->env_list, command, shell));
	return (cd_home(command->env_list));
}

static int	select_builtin(t_command *command, t_shell *shell)
{
	int	ret;

	if (ft_strncmp(command->command, "cd", 3) == 0)
		ret = handle_cd(command, shell);
	else if (ft_strncmp(command->command, "echo", 5) == 0)
		ret = echo(command);
	else if (ft_strncmp(command->command, "pwd", 4) == 0)
		ret = pwd(&command->input);
	else if (ft_strncmp(command->command, "env", 4) == 0)
		ret = env(command->env_list);
	else if (ft_strncmp(command->command, "export", 7) == 0)
		ret = run_export_builtin(command);
	else if (ft_strncmp(command->command, "unset", 6) == 0)
		ret = run_unset_builtin(command);
	else if (ft_strncmp(command->command, "exit", 5) == 0)
		ret = exit_shell(command->pattern, command, shell);
	else
	{
		ft_putstr_fd("Error: Unknown built-in command.\n", 2);
		ret = 1;
	}
	return (ret);
}

int	execute_builtin(t_command **cmd_list, t_shell *shell)
{
	t_command	*command;
	int			ret;

	command = *cmd_list;
	if (!command || !command->command)
	{
		ft_putstr_fd("Error: Invalid command structure.\n", 2);
		shell->exit_status = 1;
		return (1);
	}
	ret = select_builtin(command, shell);
	if (ret == 0)
		shell->exit_status = 0;
	return (ret);
}

/**
 * @brief Frees an array of strings.
 * Iterates over the array until a NULL pointer is found, freeing each string.
 *
 * @param args The NULL-terminated array of strings. 
 */
void	free_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}
