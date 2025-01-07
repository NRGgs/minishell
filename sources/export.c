/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:58:57 by iriadyns          #+#    #+#             */
/*   Updated: 2025/01/07 09:45:09 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int my_export(t_env **env_list, char *var)
// {
// 	t_env *env_var;
// 	char *equal_sign;
// 	char *var_name;
// 	char *var_value;
// 	t_env *new_var;

// 	equal_sign = ft_strchr(var, '=');
// 	if (!equal_sign)
// 	{
// 		ft_putstr_fd("export: invalid format, expected VAR=VALUE\n", 2);
// 		return (1);
// 	}

// 	var_name = ft_substr(var, 0, equal_sign - var);
// 	var_value = ft_strdup(equal_sign + 1);
// 	if (!var_name || !var_value)
// 	{
// 		ft_putstr_fd("export: memory allocation failed\n", 2);
// 		free(var_name);
// 		free(var_value);
// 		return (1);
// 	}

// 	env_var = get_env(*env_list, var_name);
// 	if (env_var)
// 	{
// 		free(env_var->value);
// 		env_var->value = var_value;
// 		free(var_name);
// 	}
// 	else
// 	{
// 		new_var = malloc(sizeof(t_env));
// 		if (!new_var)
// 		{
// 			ft_putstr_fd("export: memory allocation failed\n", 2);
// 			free(var_name);
// 			free(var_value);
// 			return (1);
// 		}
// 		new_var->name = var_name;
// 		new_var->value = var_value;
// 		new_var->next = *env_list;
// 		*env_list = new_var;
// 	}

// 	return (0);
// }

int my_export(t_env **env_list, char *var)
{
	t_env	*new_var;
	char	*equal_sign;
	char	*var_name;
	char	*var_value;

	equal_sign = ft_strchr(var, '=');
	if (!equal_sign)
	{
		ft_putstr_fd("export: invalid format, expected VAR=VALUE\n", 2);
		return (1);
	}

	// Разделяем переменную на имя и значение
	var_name = ft_substr(var, 0, equal_sign - var);
	var_value = ft_strdup(equal_sign + 1);
	if (!var_name || !var_value)
	{
		ft_putstr_fd("export: memory allocation failed\n", 2);
		free(var_name);
		free(var_value);
		return (1);
	}

	// Проверяем наличие переменной через getenv
	if (getenv(var_name))
	{
		// Обновляем значение существующей переменной
		if (setenv(var_name, var_value, 1) < 0)
		{
			perror("export");
			free(var_name);
			free(var_value);
			return (1);
		}
		free(var_name); // var_name больше не нужен
		free(var_value); // var_value был скопирован в setenv
	}
	else
	{
		// Добавляем новую переменную в env_list
		new_var = malloc(sizeof(t_env));
		if (!new_var)
		{
			ft_putstr_fd("export: memory allocation failed\n", 2);
			free(var_name);
			free(var_value);
			return (1);
		}
		new_var->name = var_name;
		new_var->value = var_value;
		new_var->next = *env_list;
		*env_list = new_var;
	}

	return (0);
}