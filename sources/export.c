/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:22:15 by iriadyns          #+#    #+#             */
/*   Updated: 2025/01/26 16:22:40 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env *find_env_var(t_env *env_list, const char *name)
{
	while (env_list)
	{
		if (strcmp(env_list->name, name) == 0)
			return env_list;
		env_list = env_list->next;
	}
	return NULL;
}

t_env *create_env_var(t_env **env_list, const char *name, const char *value)
{
	t_env	*new_var;
	t_env	*tmp;

	new_var = (t_env *)malloc(sizeof(t_env));
	if (!new_var)
		return NULL;
	new_var->name = strdup(name);
	if (!new_var->name)
	{
		free(new_var);
		return NULL;
	}
	if (value)
		new_var->value = strdup(value);
	else
		new_var->value = NULL;
	new_var->next = NULL;
	if (*env_list == NULL)
		*env_list = new_var;
	else
	{
		tmp = *env_list;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_var;
	}
	return new_var;
}

void print_exported_vars(t_env *env_list)
{
	t_env *tmp = env_list;

	while (tmp)
	{
		printf("declare -x %s", tmp->name);
		if (tmp->value)
			printf("=\"%s\"", tmp->value);
		printf("\n");
		tmp = tmp->next;
	}
}

int my_export(t_env **env_list, char **args)
{
	if (!args || !args[0])
	{
		print_exported_vars(*env_list);
		return (0);
	}
	int i = 0;
	while (args[i])
	{
		char *arg = args[i];
		char *equal_sign = strchr(arg, '=');

		if (equal_sign)
		{
			size_t name_len = equal_sign - arg;
			char *name = strndup(arg, name_len);
			char *value = strdup(equal_sign + 1);

			if (!name)
			{
				i++;
				continue;
			}
			t_env *existing = find_env_var(*env_list, name);
			if (existing)
			{
				free(existing->value);
				existing->value = value;
			}
			else
				create_env_var(env_list, name, value);
			free(name);
		}
		else
		{
			t_env	*existing = find_env_var(*env_list, arg);
			if (!existing)
				create_env_var(env_list, arg, NULL);
		}
		i++;
	}
	return (0);
}
