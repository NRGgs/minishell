/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:45:47 by nmattos           #+#    #+#             */
/*   Updated: 2024/12/20 12:55:07 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	clean_commands(t_command **cmds)
{
	t_command	*current;
	t_command	*next;

	current = *cmds;
	while (current != NULL)
	{
		next = current->next;
		free(current->command);
		if (current->options != NULL)
			free(current->options);
		if (current->input != NULL)
			free(current->input);
		if (current->output != NULL)
			free(current->output);
		free(current);
		current = next;
	}
	*cmds = NULL;
}
