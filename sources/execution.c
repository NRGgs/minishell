/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:20:14 by iriadyns          #+#    #+#             */
/*   Updated: 2025/01/26 16:20:53 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**environ;

void	execute_commands(t_command *commands)
{
	t_command	*current;
	int			is_pipe;

	if (!commands)
	{
		ft_putstr_fd("Error: Command structure is NULL.\n", 2);
		return ;
	}
	current = commands;
	is_pipe = 0;
	while (current)
	{
		if (current->out_type == PIPE || current->in_type == PIPE)
		{
			is_pipe = 1;
			break ;
		}
		current = current->next;
	}
	if (is_pipe)
		execution_with_pipe(commands);
	else
		execution_without_pipe(commands);
}

t_env	*create_env_node(const char *name, const char *value)
{
	t_env	*new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->name = strdup(name);
	new_node->value = (value) ? strdup(value) : NULL;
	new_node->next = NULL;
	return (new_node);
}

t_env	*init_env_list(void)
{
	t_env	*env_list = NULL;
	t_env	*tmp;
	int	i = 0;

	while (environ[i])
	{
		char	*equal_pos = strchr(environ[i], '=');
		if (equal_pos)
		{
			size_t name_len = equal_pos - environ[i];
			char	*name = strndup(environ[i], name_len);
			char	*value = strdup(equal_pos + 1);
			t_env	*new_node = create_env_node(name, value);
			free(name);
			free(value);
			if (!env_list)
				env_list = new_node;
			else
			{
				tmp = env_list;
				while (tmp->next)
					tmp = tmp->next;
				tmp->next = new_node;
			}
		}
		i++;
	}
	return (env_list);
}
