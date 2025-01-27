/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:12:55 by iriadyns          #+#    #+#             */
/*   Updated: 2025/01/27 14:18:24 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*alloc_env_node(const char *name, const char *value)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->name = strdup(name);
	if (!node->name)
	{
		free(node);
		return (NULL);
	}
	if (value)
		node->value = strdup(value);
	else
		node->value = NULL;
	node->next = NULL;
	return (node);
}

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

void	handle_export_equal(t_env **env_list, char *arg, char *equal_sign)
{
	size_t	name_len;
	char	*name;
	char	*value;
	t_env	*existing;

	name_len = equal_sign - arg;
	name = strndup(arg, name_len);
	if (!name)
		return ;
	value = strdup(equal_sign + 1);
	if (!value)
	{
		free(name);
		return ;
	}
	existing = find_env_var(*env_list, name);
	if (existing)
	{
		free(existing->value);
		existing->value = value;
	}
	else
		create_env_var(env_list, name, value);
	free(name);
}

void	handle_export_no_equal(t_env **env_list, char *arg)
{
	t_env	*existing;

	existing = find_env_var(*env_list, arg);
	if (!existing)
		create_env_var(env_list, arg, NULL);
}

void	process_export_arg(t_env **env_list, char *arg)
{
	char	*equal_sign;

	equal_sign = strchr(arg, '=');
	if (equal_sign)
		handle_export_equal(env_list, arg, equal_sign);
	else
		handle_export_no_equal(env_list, arg);
}
