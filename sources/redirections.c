/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmattos <nmattos@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/03 15:01:53 by nmattos       #+#    #+#                 */
/*   Updated: 2024/12/04 10:55:22 by nmattos       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"

int	textfile_redirection(char *filename, char *redirection, t_command **last)
{
	if (ft_strcmp(redirection, ">") == 0 || ft_strcmp(redirection, ">>") == 0)
	{
		(*last)->output = ft_strdup(filename);
		if (ft_strcmp(redirection, ">>") == 0)
			(*last)->out_type = APPEND;
		else
			(*last)->out_type = TEXTFILE;
		if ((*last)->output == NULL)
			return (FAIL);
	}
	else if (ft_strcmp(redirection, "<") == 0)
	{
		(*last)->input = ft_strdup(filename);
		(*last)->in_type = TEXTFILE;
		if ((*last)->input == NULL)
			return (FAIL);
	}
	return (SUCCESS);
}

static char	*add_newline(char *input)
{
	char	*temp;

	if (input[0] == '\0')
		return (input);
	temp = ft_strjoin(input, "\n");
	if (temp == NULL)
	{
		free(input);
		return (NULL);
	}
	free(input);
	input = ft_strdup(temp);
	free(temp);
	return (input);
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
