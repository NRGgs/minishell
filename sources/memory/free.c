/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmattos- <nmattos-@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/05 15:40:40 by nmattos-      #+#    #+#                 */
/*   Updated: 2025/02/25 15:55:28 by nmattos       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Frees the memory of a pointer and sets it to NULL.
 *
 * @param ptr The pointer to be freed.
 *
 * @return None.
 */
void	free_null(void **ptr)
{
	if (ptr != NULL || *ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

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
