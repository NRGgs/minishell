/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:22:15 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/08 13:15:08 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * @brief Finds an environment variable in the list by name.
 *
 * @param env_list The environment list.
 *
 * @param name The variable name.
 *
 * @return Pointer to the found environment node, or NULL.
 */
t_env	*find_env_var(t_env *env_list, const char *name)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->name, name) == 0)
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

/**
 * @brief Creates a new environment variable node and adds it to the list.
 *
 * @param env_list Pointer to the environment list.
 *
 * @param name The variable name.
 *
 * @param value The variable value.
 *
 * @return Pointer to the new node, or NULL on failure.
 */
t_env	*create_env_var(t_env **env_list, const char *name, const char *value)
{
	t_env	*new_var;

	new_var = alloc_env_node(name, value);
	if (!new_var)
		return (NULL);
	add_env_to_list(env_list, new_var);
	return (new_var);
}

/**
 * @brief Prints exported environment variables.
 *
 * @param env_list The environment list.
 */
void	print_exported_vars(t_env *env_list)
{
	t_env	*tmp;

	tmp = env_list;
	while (tmp)
	{
		printf("declare -x %s", tmp->name);
		if (tmp->value)
			printf("=\"%s\"", tmp->value);
		printf("\n");
		tmp = tmp->next;
	}
}

/**
 * @brief Implements the export built-in command.
 *
 * @param env_list Pointer to the environment list.
 *
 * @param args The export arguments.
 *
 * @return 0 on success
 */
int	my_export(t_env **env_list, char **args, t_shell *shell)
{
	int	i;

	if (!args || !args[0])
	{
		print_exported_vars(*env_list);
		return (shell->exit_status);
	}
	i = 0;
	while (args[i])
	{
		process_export_arg(env_list, args[i], shell);
		i++;
	}
	return (shell->exit_status);
}

/**
 * @brief Executes the export built-in command.
 *
 * @param command The export command structure.
 *
 * @return The exit status.
 */
int	run_export_builtin(t_command *command, t_shell *shell)
{
	char	*pattern_dup;
	char	*args[2];
	int		ret;

	if (!command->pattern && command->options == NULL)
	{
		print_exported_vars(command->env_list);
		return (0);
	}
	if (command->options)
	{
		printf("minishell: %s: invalid option\n", command->options);
		return (2);
	}
	pattern_dup = ft_strdup(command->pattern);
	if (!pattern_dup)
		return (FAIL);
	args[0] = pattern_dup;
	args[1] = NULL;
	ret = my_export(&(command->env_list), args, shell);
	return (ret);
}
