/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   necessary.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:36:05 by nmattos           #+#    #+#             */
/*   Updated: 2025/02/26 12:28:26 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Check if the character is valid.
 *
 * @param c The character to be checked.
 * @return true if the character is valid, false otherwise.
 */
bool	valid_char(char c)
{
	if ((c >= 65 && c <= 90)
		|| (c >= 97 && c <= 122)
		|| (c >= 48 && c <= 57))
		return (true);
	return (false);
}

/**
 * @brief Attaches a buffer to the end of the string.
 *
 * @param pattern The string to attach the buffer to.
 * @param buffer The buffer to attach.
 * @return A new string with the buffer attached.
 */
static char	*attach_buffer(char *pattern, char *buffer)
{
	char	*temp;

	pattern = add_newline(pattern);
	if (pattern == NULL)
		return (free(buffer), NULL);
	temp = ft_strjoin(pattern, buffer);
	free(buffer);
	if (temp == NULL)
		return (free(pattern), NULL);
	free(pattern);
	pattern = ft_strdup(temp);
	if (pattern == NULL)
		return (free(temp), NULL);
	free(temp);
	return (pattern);
}

/**
 * @brief Reads from the terminal until a quote is given by the user.
 *
 * @param delimiter The quote to look for (single or double).
 * @param pattern The string to attach the input to.
 * @return The string with the input attached.
 */
char	*read_till_quotes(char delimiter, char **pattern)
{
	char	*buffer;
	bool	reading;
	int		stdin_backup;

	stdin_backup = dup(STDIN_FILENO);
	signal(SIGINT, signal_heredoc);
	reading = true;
	while (reading)
	{
		buffer = readline("\\ ");
		if (buffer == NULL)
		{
			restore_stdin(stdin_backup, pattern);
			return (NULL);
		}
		if (buffer != NULL && ft_strchr(buffer, delimiter) != NULL)
			reading = false;
		*pattern = attach_buffer(*pattern, buffer);
		if (*pattern == NULL)
			return (NULL);
	}
	return (*pattern);
}
