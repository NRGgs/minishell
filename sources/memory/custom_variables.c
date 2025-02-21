/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 12:09:56 by nmattos           #+#    #+#             */
/*   Updated: 2025/02/21 11:14:32 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*	Create a new variable.
 *
 *	name:	the name of the variable.
 *	value:	the value of the variable.
 *
 *	Return: the new variable.
 */
t_variable	*var_new(char *name, char *value)
{
	t_variable	*new_var;

	new_var = malloc(sizeof(t_variable));
	if (new_var == NULL)
		return (NULL);
	new_var->name = ft_strdup(name);
	if (new_var->name == NULL)
	{
		free(new_var);
		return (NULL);
	}
	new_var->value = ft_strdup(value);
	if (new_var->value == NULL)
	{
		free(new_var->name);
		free(new_var);
		return (NULL);
	}
	new_var->next = NULL;
	return (new_var);
}

/*	Return the last variable in the linked list.
 *
 *	vars:	the linked list of variables.
 *
 *	Return: the last variable.
 */
t_variable	*var_last(t_variable *vars)
{
	t_variable	*last;

	if (vars == NULL)
		return (NULL);
	last = vars;
	while (last->next != NULL)
		last = last->next;
	return (last);
}

/*	Add a new variable to the end of the linked list.
 *
 *	vars		the start of the linked list.
 *	new_var:	the new variable to be added.
 *
 * 	Return: void.
 */
void	var_add_back(t_variable **vars, t_variable *new_var)
{
	t_variable	*last;

	if (*vars == NULL)
		*vars = new_var;
	else
	{
		last = var_last(*vars);
		last->next = new_var;
	}
}

/*	Find a variable in the linked list.
 *
 *	vars:	the linked list of variables.
 *	name:	the name of the variable to be found.
 *
 *	Return: the variable.
 *			NULL if not found.
 */
t_variable	*var_find(t_variable *vars, char *name)
{
	t_variable	*current;

	current = vars;
	while (current != NULL)
	{
		if (ft_strcmp(current->name, name) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}
