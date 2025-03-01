/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmattos- <nmattos-@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/26 16:24:43 by iriadyns      #+#    #+#                 */
/*   Updated: 2025/03/01 17:02:19 by nmattos       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * @brief Removes an environment variable from the list.
 *
 * @param env_list Pointer to the environment list.
 *
 * @param var_name The name of the variable to remove.
 *
 * @return 1 if removed, 0 otherwise.
 */
int	remove_env_var(t_env **env_list, const char *var_name)
{
	t_env	*current;
	t_env	*prev;

	current = *env_list;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->name, var_name) == 0)
		{
			if (!prev)
				*env_list = current->next;
			else
				prev->next = current->next;
			free(current->name);
			free(current->value);
			free(current);
			return (1);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}

/**
 * @brief Implements the unset built-in command.
 * Removes environment variables specified in args.
 *
 * @param env_list Pointer to the environment list.
 *
 * @param args The unset arguments.
 *
 * @return 0 on success.
 */
int	my_unset(t_env **env_list, char **args)
{
	int	i;

	i = 0;
	if (!args || !args[0])
	{
		return (0);
	}
	while (args[i])
	{
		remove_env_var(env_list, args[i]);
		i++;
	}
	return (0);
}

/**
 * @brief Executes the unset built-in command.
 *
 * @param command The unset command structure.
 *
 * @return The exit status.
 */
int	run_unset_builtin(t_command *command, t_shell *shell)
{
	char	*argument;
	char	*args[2];
	int		ret;

	if (!command->pattern)
	{
		return (FAIL);
	}
	argument = ft_strdup(command->pattern);
	if (!argument)
		return (FAIL);
	if (prepare_arg(command->env_list, &argument, shell) == FAIL)
	{
		free(argument);
		return (FAIL);
	}
	args[0] = argument;
	args[1] = NULL;
	ret = my_unset(&(command->env_list), args);
	free(argument);
	return (ret);
}
