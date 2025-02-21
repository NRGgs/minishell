/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:12:55 by iriadyns          #+#    #+#             */
/*   Updated: 2025/02/21 12:27:45 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * @brief Allocates a new environment node.
 *
 * @param name The variable name.
 *
 * @param value The variable value.
 *
 * @return Pointer to the new node, or NULL on failure.
 */
t_env	*alloc_env_node(const char *name, const char *value)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->name = ft_strdup(name);
	if (!node->name)
	{
		free(node);
		return (NULL);
	}
	if (value)
		node->value = ft_strdup(value);
	else
		node->value = NULL;
	node->next = NULL;
	return (node);
}

/**
 * @brief Adds a new environment variable node to the end of the list.
 *
 * @param env_list Pointer to the environment list.
 *
 * @param new_var The new environment node.
 */
void	add_env_to_list(t_env **env_list, t_env *new_var)
{
	t_env	*tmp;

	if (!*env_list)
		*env_list = new_var;
	else
	{
		tmp = *env_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_var;
	}
}

/**
 * @brief Handles export arguments containing '='.
 * Updates an existing variable or creates a new one.
 *
 * @param env_list Pointer to the environment list.
 *
 * @param arg The export argument.
 *
 * @param equal_sign Pointer to the '=' character in arg.
 */
void	handle_export_equal(t_env **env_list, char *arg, char *equal_sign)
{
	size_t	name_len;
	char	*name;
	char	*value;
	t_env	*existing;

	name_len = equal_sign - arg;
	name = ft_strndup(arg, name_len);
	if (!name)
		return ;
	value = ft_strdup(equal_sign + 1);
	if (!value)
		return (free(name), (void)0);
	existing = find_env_var(*env_list, name);
	if (existing)
	{
		free(existing->value);
		existing->value = value;
	}
	else
	{
		create_env_var(env_list, name, value);
		free(value);
	}
	free(name);
}

/**
 * @brief Handles export arguments without '='.
 * Adds the variable to the environment list if it does not exist.
 *
 * @param env_list Pointer to the environment list.
 *
 * @param arg The export argument.
 */
void	handle_export_no_equal(t_env **env_list, char *arg)
{
	t_env	*existing;

	existing = find_env_var(*env_list, arg);
	if (!existing)
		create_env_var(env_list, arg, NULL);
}

/**
 * @brief Processes a single export argument.
 *
 * @param env_list Pointer to the environment list.
 *
 * @param arg The export argument.
 */
void	process_export_arg(t_env **env_list, char *arg)
{
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		if (prepare_arg(*env_list, &arg) == FAIL)
			return ;
		equal_sign = ft_strchr(arg, '=');
		handle_export_equal(env_list, arg, equal_sign);
		free(arg);
	}
	else
	{
		handle_export_no_equal(env_list, arg);
		free(arg);
	}
}
