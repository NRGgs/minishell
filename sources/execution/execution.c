/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:20:14 by iriadyns          #+#    #+#             */
/*   Updated: 2025/02/24 18:40:59 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern char	**environ;

/**
 * @brief Executes the list of commands.
 * Scans the linked list of commands to decide
 * whether to use pipe execution or not.
 *
 * @param commands The linked list of commands.
 *
 * @return The shell exit status.
 */
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

/**
 * @brief Creates a new environment node with the given name and value.
 * Allocates memory for a new t_env structure, duplicates the name and value,
 * and initializes the next pointer to NULL.
 *
 * @param name The environment variable name.
 *
 * @param value The environment variable value.
 *
 * @return Pointer to the new node or NULL on failure.
 */
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

int	count_tokens(char **arr)
{
	int	cnt;

	cnt = 0;
	while (arr && arr[cnt])
		cnt++;
	return (cnt);
}
