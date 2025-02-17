/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:46:46 by nmattos-          #+#    #+#             */
/*   Updated: 2025/02/17 10:40:00 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	parse_options(char **input, int *i, char **options);
static char	*get_pattern(char **input, int *i, char *pattern);

/**
 * @brief Parse the command and its options.
 *
 * @param input The user input.
 * @param cmds The linked list of commands.
 * @param i The index of the current token.
 *
 * @return SUCCESS (1) / FAIL (0).
 */
static int	parse_options(char **input, int *i, char **options)
{
	size_t		size;
	int			j;

	size = 0;
	j = *i;
	while (input[j + 1] != NULL && input[j + 1][0] == '-')
	{
		j++;
		size += ft_strlen(input[j]);
	}
	if (size <= 0)
		return (SUCCESS);
	size += j - (*i)++;
	*options = ft_calloc((size + 1), sizeof(char));
	if (*options == NULL)
		return (FAIL);
	while (input[*i] != NULL && input[*i][0] == '-')
	{
		ft_strlcat(*options, input[*i], size + 1);
		if (input[*i + 1] != NULL && input[*i + 1][0] == '-')
			ft_strlcat(*options, " ", size);
		(*i)++;
	}
	(*i)--;
	return (SUCCESS);
}

/**
 * Get the pattern of the command.
 *
 * @param input   the user input.
 * @param i       the index of the current token.
 * @param pattern the pattern of the command.
 *
 * @return the new pattern.
 */
static char	*get_pattern(char **input, int *i, char *pattern)
{
	char	*new_pattern;
	size_t	len_pattern;
	size_t	len_string;

	new_pattern = NULL;
	len_pattern = 0;
	len_string = 0;
	while (input[*i + 1] != NULL && !is_command(input[*i + 1])
		&& !is_redirect(input[*i + 1]))
	{
		len_string = ft_strlen(input[*i + 1]);
		if (pattern == NULL)
			new_pattern = ft_strdup(input[*i + 1]);
		else
		{
			len_pattern = ft_strlen(pattern) + 1;
			new_pattern = ft_strndup(pattern, len_pattern + len_string);
			space_strlcat(new_pattern, input[*i + 1], \
				len_pattern + len_string + 1);
		}
		free(pattern);
		pattern = new_pattern;
		(*i)++;
	}
	return (new_pattern);
}
