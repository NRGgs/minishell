/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_string_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:03:25 by nmattos-          #+#    #+#             */
/*   Updated: 2025/02/03 14:08:06 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	n_chars_till_quote(char **input, int j)
{
	int		start;
	int		k;
	size_t	size;

	size = 0;
	start = j - 1;
	while (input[j] != NULL)
	{
		if (ft_strchr(input[j], '\"') != NULL)
		{
			k = 0;
			while (input[j][k] != '\"')
			{
				size++;
				k++;
			}
			return (size + (j - start));
		}
		size += ft_strlen(input[j]) + 1;
		j++;
	}
	return (size);
}

char	*read_till_quotes(char *delimiter, char **pattern)
{
	char	*buffer;
	char	*temp;

	while (1)
	{
		buffer = readline("\\ ");
		if (buffer != NULL && ft_strcmp(buffer, delimiter) == 0)
		{
			free(buffer);
			break ;
		}
		*pattern = add_newline(*pattern);
		if (*pattern == NULL)
			return (free(buffer), NULL);
		temp = ft_strjoin(*pattern, buffer);
		free(buffer);
		if (temp == NULL)
			return (free(*pattern), NULL);
		free(*pattern);
		*pattern = ft_strdup(temp);
		if (*pattern == NULL)
			return (free(temp), NULL);
		free(temp);
	}
	return (*pattern);
}
