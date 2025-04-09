/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:40:40 by nmattos-          #+#    #+#             */
/*   Updated: 2025/04/09 14:19:02 by nmattos-         ###   ########.fr       */
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
		cmd_clear(&current);
		current = next;
	}
	*cmds = NULL;
}

/**
 * @brief Clean the redirects linked list
 *
 * @param node The linked list to clean
 */
void	clean_redirect(t_redirect **node)
{
	t_redirect	*current;
	t_redirect	*next;

	current = *node;
	while (current != NULL)
	{
		next = current->next;
		free_null((void **)&current->arg);
		free_null((void **)&current);
		current = next;
	}
	*node = NULL;
}

/**
 * @brief Clean a single command
 *
 * @param cmd The command to clean
 */
void	cmd_clear(t_command **cmd)
{
	clean_redirect(&(*cmd)->redirect);
	free_null((void **)&(*cmd)->command);
	free_null((void **)&(*cmd)->options);
	free_null((void **)&(*cmd)->pattern);
	free_null((void **)cmd);
}
