/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:20:14 by iriadyns          #+#    #+#             */
/*   Updated: 2025/02/12 14:02:38 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**environ;

int	is_directory(const char *path)
{
	struct stat	st;

	if (stat(path, &st) != 0)
		return (0);
	return (S_ISDIR(st.st_mode));
}

int	execute_commands(t_command *commands)
{
	t_command	*current;
	int			is_pipe;
	int			ret;

	if (!commands)
	{
		ft_putstr_fd("Error: Command structure is NULL.\n", 2);
		return (SHELL_CONTINUE);
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
		ret = execution_with_pipe(commands);
	else
		ret = execution_without_pipe(commands);
	return (ret);
}

t_env	*create_env_node(const char *name, const char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->name = ft_strdup(name);
	if (value)
		new_node->value = ft_strdup(value);
	else
		new_node->value = NULL;
	new_node->next = NULL;
	return (new_node);
}
