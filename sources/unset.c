/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:24:43 by iriadyns          #+#    #+#             */
/*   Updated: 2025/01/26 16:25:17 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	remove_env_var(t_env **env_list, const char *var_name)
{
	t_env	*current = *env_list;
	t_env	*prev = NULL;

	while (current)
	{
		if (strcmp(current->name, var_name) == 0)
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

int my_unset(t_env **env_list, char **args)
{
	int i = 0;

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

char **parse_args_for_unset(t_command *command)
{
	if (!command->pattern)
		return (NULL);
	return ft_split(command->pattern, ' ');
}
