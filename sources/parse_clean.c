/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:45:47 by nmattos           #+#    #+#             */
/*   Updated: 2025/02/17 10:45:00 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Clean a two dimensional array
 *
 * @param array The array to clean
 */
void	clean_2d_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

/**
 * @brief Clean the variables linked list
 *
 * @param vars The linked list to clean
 */
void	clean_variables(t_variable **vars)
{
	t_variable	*current;
	t_variable	*next;

	current = *vars;
	while (current != NULL)
	{
		next = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = next;
	}
	*vars = NULL;
}

/**
 * @brief Clean the commands linked list
 *
 * @param cmds The linked list to clean
 */
void	clean_commands(t_command **cmds)
{
	t_command	*current;
	t_command	*next;

	current = *cmds;
	while (current != NULL)
	{
		next = current->next;
		free_null((void **)&current->command);
		free_null((void **)&current->options);
		free_null((void **)&current->input);
		free_null((void **)&current->output);
		free_null((void **)&current->pattern);
		free(current);
		current = next;
	}
	*cmds = NULL;
}
