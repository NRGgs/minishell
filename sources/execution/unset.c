/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:00:28 by iriadyns          #+#    #+#             */
/*   Updated: 2024/12/04 14:00:29 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int unset(t_env *env_list, char *var)
{
	t_env *prev;
	t_env *current;
	unsigned int len;

	len = ft_strlen(var);
	current = env_list;
	prev = NULL;

	while (current)
	{
		if (ft_strlen(current->name) == len && ft_strncmp(current->name, var, len) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				env_list = current->next;
			free(current->name);
			free(current->value);
			free(current);
			return (0);
		}
		prev = current;
		current = current->next;
	}

	ft_putstr_fd("unset: variable not found\n", 2);
	return (1);
}
