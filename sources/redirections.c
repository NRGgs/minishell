/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:01:53 by nmattos           #+#    #+#             */
/*   Updated: 2025/02/03 14:16:58 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

static char	*read_here_doc(char *delimiter, char *input)
{
	char	*buffer;
	char	*temp;

	while (1)
	{
		buffer = readline("heredoc> ");
		if (buffer != NULL && ft_strcmp(buffer, delimiter) == 0)
		{
			free(buffer);
			break ;
		}
		input = add_newline(input);
		if (input == NULL)
			return (free(buffer), NULL);
		temp = ft_strjoin(input, buffer);
		free(buffer);
		if (temp == NULL)
			return (free(input), NULL);
		free(input);
		input = ft_strdup(temp);
		if (input == NULL)
			return (free(temp), NULL);
		free(temp);
	}
	return (input);
}

int	here_doc_redirection(char *delimiter, t_command **last)
{
	char	*input;

	(*last)->in_type = HERE_DOC;
	input = ft_calloc(1, 1);
	if (input == NULL)
		return (FAIL);
	input = read_here_doc(delimiter, input);
	if (input == NULL)
		return (FAIL);
	(*last)->input = input;
	return (SUCCESS);
}

char	*join_strings(char *str, char *temp, size_t size)
{
	ft_strlcat(temp, str, size + 1);
	if (str != NULL
		&& str[ft_strlen(str) - 1] != '\"'
		&& str[ft_strlen(str) - 1] != '\'')
		ft_strlcat(temp, " ", size + 1);
	return (temp);
}

/*	Parses string and sets it as input.
 *
 *	input: user input split by ' '
 *	cmds: linked list of commands
 *	i: index of current token
 *
 *	Return: SUCCESS (1) / FAIL (0).
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
