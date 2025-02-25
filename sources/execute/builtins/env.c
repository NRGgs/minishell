/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:56:48 by iriadyns          #+#    #+#             */
/*   Updated: 2025/02/21 11:14:07 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * @brief Prints the environment variables.
 *
 * @param env_list The environment list.
 *
 * @return 0
 */
int	env(t_env *env_list)
{
	t_env	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->name, tmp->value);
		else
			printf("%s=\n", tmp->name);
		tmp = tmp->next;
	}
	return (0);
}
