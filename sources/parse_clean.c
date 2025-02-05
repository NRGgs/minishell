/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:45:47 by nmattos           #+#    #+#             */
/*   Updated: 2025/02/05 16:43:57 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*	Clean a two dimensional array
 *
 *	array:	the array to clean
 *
 *	Return: none.
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

/*	Clean the variables linked list
 *
 *	vars:	the linked list to clean
 *
 *	Return: none.
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

/*	Clean the commands linked list
 *
 *	cmds:	the linked list to clean
 *
 *	Return: none.
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
