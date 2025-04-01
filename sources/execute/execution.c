/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:20:14 by iriadyns          #+#    #+#             */
/*   Updated: 2025/04/01 14:28:29 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern char	**environ;

static int	check_commands_for_pipe(t_command *commands, t_shell *shell)
{
	t_command	*current;
	int			is_pipe;

	is_pipe = 0;
	current = commands;
	while (current)
	{
		if ((!current->command || current->command[0] == '\0'))
		{
			if (current->redirect)
			{
				current->command = ft_strdup("cat");
				if (!current->command)
				{
					ft_putstr_fd("minishell: allocation error\n", 2);
					shell->exit_status = 2;
					return (2);
				}
			}
			else
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
				shell->exit_status = 2;
				return (2);
			}
		}
		if (current->next != NULL)
		{
			is_pipe = 1;
			break ;
		}
		current = current->next;
	}
	return (is_pipe);
}

int	execute_commands(t_command *commands, t_shell *shell)
{
	int	is_pipe;
	int	ret;

	if (!commands)
	{
		ft_putstr_fd("Error: Command structure is NULL.\n", 2);
		return (SHELL_CONTINUE);
	}
	is_pipe = check_commands_for_pipe(commands, shell);
	if (is_pipe == -1)
		return (SHELL_CONTINUE);
	if (is_pipe)
		ret = execution_with_pipe(commands, shell);
	else
		ret = execution_without_pipe(commands, shell);
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

static int	ft_isspace(int c)
{
	return ((c == ' ')
		|| (c >= 9 && c <= 13));
}

int	is_all_whitespace(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}
