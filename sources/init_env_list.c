/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:00:24 by iriadyns          #+#    #+#             */
/*   Updated: 2025/01/28 13:02:28 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**environ;

int	parse_env_var(char *env_str, char **name, char **value)
{
	char	*equal_pos;
	size_t	name_len;

	equal_pos = strchr(env_str, '=');
	if (!equal_pos)
		return (FAIL);
	name_len = equal_pos - env_str;
	*name = strndup(env_str, name_len);
	if (!*name)
		return (FAIL);
	*value = strdup(equal_pos + 1);
	if (!*value)
	{
		free(*name);
		return (FAIL);
	}
	return (SUCCESS);
}

void	append_env_node(t_env **list, t_env *new_node)
{
	t_env	*tmp;

	if (!*list)
	{
		*list = new_node;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

t_env	*init_env_list(void)
{
	t_env	*env_list;
	char	*name;
	char	*value;
	t_env	*new_node;
	int		i;

	env_list = NULL;
	i = 0;
	while (environ[i])
	{
		if (parse_env_var(environ[i], &name, &value) == SUCCESS)
		{
			new_node = create_env_node(name, value);
			free(name);
			free(value);
			if (new_node)
				append_env_node(&env_list, new_node);
		}
		i++;
	}
	return (env_list);
}
