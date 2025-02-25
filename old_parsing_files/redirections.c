/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:01:53 by nmattos           #+#    #+#             */
/*   Updated: 2025/02/24 12:32:36 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Handles textfile redirections.
 *
 * @param fn        Filename.
 * @param redirect  Redirection type (">", ">>", "<").
 * @param last      Linked list of commands.
 * @param place     Place of 'redirect' in relation to the command.
 *
 *	@return	SUCCESS (1) / FAIL (0).
 */
int	textfile_redirection(char *fn, char *redirect, t_command **last, int place)
{
	if (ft_strcmp(redirect, ">") == 0 || ft_strcmp(redirect, ">>") == 0)
	{
		(*last)->output = ft_strdup(fn);
		if (ft_strcmp(redirect, ">>") == 0)
			(*last)->out_type = APPEND;
		else if (place == AFTER)
			(*last)->out_type = TEXTFILE;
		else if (place == BEFORE)
			(*last)->in_type = TEXTFILE;
		if ((*last)->output == NULL)
			return (FAIL);
	}
	else if (ft_strcmp(redirect, "<") == 0)
	{
		(*last)->input = ft_strdup(fn);
		if (place == AFTER)
			(*last)->in_type = TEXTFILE;
		else if (place == BEFORE)
			(*last)->out_type = TEXTFILE;
		if ((*last)->input == NULL)
			return (FAIL);
	}
	return (SUCCESS);
}

/**
 * Concatenates strings and adds a space between them.
 *
 * @param str: string to concatenate
 * @param temp: string to concatenate to
 * @param size: size of the new string
 *
 * @return new string.
 */
char	*join_strings(char *str, char *temp, size_t size)
{
	ft_strlcat(temp, str, size + 1);
	if (str != NULL
		&& str[ft_strlen(str) - 1] != '\"'
		&& str[ft_strlen(str) - 1] != '\'')
		ft_strlcat(temp, " ", size + 1);
	return (temp);
}

/**
 * Handles textfile redirections.
 *
 * @param fn        Filename.
 * @param redirect  Redirection type (">", ">>", "<").
 * @param last      Linked list of commands.
 * @param place     Place of 'redirect' in relation to the command.
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
