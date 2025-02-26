/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:00:24 by iriadyns          #+#    #+#             */
/*   Updated: 2025/02/26 10:44:12 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern char	**environ;

/**
 * @brief Parses an environment variable string into its name and value.
 * This function looks for the first '=' character in the provided
 * environment string (e.g. "PATH=/usr/bin") and splits it into a name
 * and value. Memory for the name and value is allocated
 *
 * @param env_str The environment string.
 *
 * @param name Pointer to where the allocated name will be stored.
 *
 * @param value Pointer to where the allocated value will be stored.
 *
 * @return SUCCESS if parsing succeeded, otherwise FAIL.
 */
int	parse_env_var(char *env_str, char **name, char **value)
{
	char	*equal_pos;
	size_t	name_len;

	equal_pos = ft_strchr(env_str, '=');
	if (!equal_pos)
		return (FAIL);
	name_len = equal_pos - env_str;
	*name = ft_strndup(env_str, name_len);
	if (!*name)
		return (FAIL);
	*value = ft_strdup(equal_pos + 1);
	if (!*value)
	{
		free(*name);
		return (FAIL);
	}
	return (SUCCESS);
}

/**
 * @brief Appends a new environment node to the linked list.
 *
 * @param list Pointer to the pointer to the environment list.
 *
 * @param  new_node The new environment node to append.
 */
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

/**
 * @brief Initializes the environment list from the global environ.
 * Iterates over the global environ array and uses parse_env_var()
 * and create_env_node() to build a linked list of environment variables.
 *
 * @return Pointer to the head of the environment list.
 */
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

/**
 * @brief Frees the entire environment list.
 * Iterates over the linked list and frees the memory
 * allocated for each node’s name, value and the node itself.
 *
 * @param env_list The head of the environment list.
 */
void	clear_env_list(t_env *env_list)
{
	t_env	*tmp;

	while (env_list)
	{
		tmp = env_list;
		env_list = env_list->next;
		free(tmp->name);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}
