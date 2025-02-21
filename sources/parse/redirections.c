/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:01:53 by nmattos           #+#    #+#             */
/*   Updated: 2025/02/21 12:45:35 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Handles textfile redirections.
 *
 * @param fn        Filename.
 * @param redirect  Redirection type (">", ">>", "<").
 * @param last      Linked list of commands.
 * @param place     Place of 'redirect' in relation to the command (AFTER / BEFORE).
 *
 * @return SUCCESS (1) / FAIL (0).
 */
int	string_redirection(char **input, t_command **last, int *i)
{
	char	*temp;
	size_t	size;
	int		j;

	j = *i;
	size = 0;
	while (input[j] != NULL && (input[j][ft_strlen(input[j]) - 1] != '\"'
		&& input[j][ft_strlen(input[j]) - 1] != '\''))
		size += ft_strlen(input[j++]);
	size += ft_strlen(input[j]) + (j - *i) - 2;
	temp = ft_calloc(size + 1, sizeof(char));
	if (temp == NULL)
		return (FAIL);
	temp = join_strings(input[*i] + 1, temp, size);
	*i += 1;
	while (*i <= j)
	{
		temp = join_strings(input[*i], temp, size);
		*i += 1;
	}
	(*last)->input = temp;
	(*last)->in_type = STRING;
	return (SUCCESS);
}
