/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:58:57 by iriadyns          #+#    #+#             */
/*   Updated: 2024/12/20 12:56:06 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int my_export(t_env *env_list, char *var)
{
	t_env *env_var;
	char *equal_sign;
	char *var_name;
	char *var_value;

	equal_sign = ft_strchr(var, '=');
	if (!equal_sign)
	{
		ft_putstr_fd("export: invalid format, expected VAR=VALUE\n", 2);
		return (1);
	}

	var_name = ft_substr(var, 0, equal_sign - var);
	var_value = ft_strdup(equal_sign + 1);

	if (!var_name || !var_value)
	{
		ft_putstr_fd("export: memory allocation failed\n", 2);
		return (1);
	}

	env_var = get_env(env_list, var_name);
	if (env_var)
	{
		free(env_var->value);
		env_var->value = var_value;
	}
	else
	{
		t_env *new_var = malloc(sizeof(t_env));
		if (!new_var)
		{
			ft_putstr_fd("export: memory allocation failed\n", 2);
			return (1);
		}
		new_var->name = var_name;
		new_var->value = var_value;
		new_var->next = env_list;
		env_list = new_var;
	}

	return (0);
}
