/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:46:46 by nmattos-          #+#    #+#             */
/*   Updated: 2025/01/28 15:09:43 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	space_strlcat(char *dst, char *src, size_t size)
{
	ft_strlcat(dst, " ", size);
	ft_strlcat(dst, src, size);
}

/*	Check all paths in the PATH environment variable for the command.
 *
 *	cmd:	the command to be checked.
 *	path:	the PATH environment variable.
 *
 * 	Return: SUCCESS (1) / FAIL (0).
 */
static int	check_path(char *cmd, char *path)
{
	char	*start;
	char	*end;
	char	single_path[1024];

	start = path;
	end = ft_strchr(start, ':');
	while (end != NULL)
	{
		*end = '\0';
		ft_strlcpy(single_path, start, 1024);
		ft_strlcat(single_path, "/", 1024);
		ft_strlcat(single_path, cmd, 1024);
		if (access(single_path, F_OK) == 0)
			return (SUCCESS);
		start = end + 1;
		end = ft_strchr(start, ':');
	}
	ft_strlcpy(single_path, start, 1024);
	ft_strlcat(single_path, "/", 1024);
	ft_strlcat(single_path, cmd, 1024);
	if (access(single_path, F_OK) == 0)
		return (SUCCESS);
	return (FAIL);
}

/*	Check if the command is a built-in command.
 *
 *	cmd: the command to be checked.
 *
 * 	Return: SUCCESS (1) / FAIL (0) / ERROR (-1).
 */
int	is_command(char *cmd)
{
	char	*path_env;
	char	*path;
	int		found;

	path_env = getenv("PATH");
	if (path_env == NULL)
		return (ERROR);
	path = ft_strdup(path_env);
	if (path == NULL)
		return (ERROR);
	found = check_path(cmd, path);
	free(path);
	return (found);
}

/*	Check if the command is a command with string input
 *
 *	command: the command to be checked.
 *
 * 	Return: true (1) / false (0).
 */
static bool	is_special(char *command)
{
	if (ft_strncmp(command, "grep", 5) == 0
		|| ft_strncmp(command, "fgrep", 6) == 0
		|| ft_strncmp(command, "egrep", 6) == 0
		|| ft_strncmp(command, "awk", 4) == 0
		|| ft_strncmp(command, "sed", 4) == 0
		|| ft_strncmp(command, "find", 4) == 0
		|| ft_strncmp(command, "cd", 3) == 0
		|| ft_strncmp(command, "cat", 3) == 0
		|| ft_strncmp(command, "unset", 6) == 0
		|| ft_strncmp(command, "echo", 5) == 0
		|| ft_strncmp(command, "pwd", 4) == 0
		|| ft_strncmp(command, "env", 4) == 0
		|| ft_strncmp(command, "exit", 5) == 0)
		return (true);
	return (false);
}

/*	Check if the string is a redirect.
 *
 *	str: the string to be checked.
 *
 * 	Return: true (1) / false (0).
 */
static bool	is_redirect(char *str)
{
	if (ft_strcmp(str, ">") == 0 || ft_strcmp(str, ">>") == 0
		|| ft_strcmp(str, "<") == 0 || ft_strcmp(str, "<<") == 0
		|| ft_strcmp(str, "|") == 0)
	{
		return (true);
	}
	return (false);
}

static int	parse_string_helper(char *first, char *second, char **options)
{
	size_t	size;

	size = second - first;
	*options = ft_calloc((size + 1), sizeof(char));
	if (*options == NULL)
		return (FAIL);
	ft_strlcpy(*options, first + 1, size);
}

/*	Parse the string of the special commands.
 *
 *	input:		the user input.
 *	i:			the index of the current token.
 *	options:	the options of the command.
 *
 *	Return: SUCCESS (1) / FAIL (0).
 */
static int	parse_string(char **input, int *i, char **options)
{
	size_t	size;
	int		j;
	char	*first;
	char	*second;

	size = 0;
	j = *i;
	first = ft_strchr(input[j], '\"');
	second = ft_strchr(first + 1, '\"');
	if (first != second && second != NULL)
		parse_string_helper(first, second, options);
	size = ft_strlen(first);
	if (second == NULL)
	{
		while (input[j + 1] != NULL)
		{
			second = ft_strchr(input[j + 1], '\"');
			if (second != NULL)
			{
				size += (second - input[j + 1]) + 1;
				*options = ft_calloc((size + 1), sizeof(char));
				if (*options == NULL)
					return (FAIL);
				ft_strlcat(*options, first + 1, size);
				(*i)++;
				while (*i < j + 1)
					space_strlcat(*options, input[(*i)++], size);
				space_strlcat(*options, input[*i], size);
				break ;
			}
			size += ft_strlen(input[j + 1]) + 1;
			j++;
		}
	}
	return (SUCCESS);
}

/*	Parse the pattern of the special commands.
 *
 *	input:		the user input.
 *	i:			the index of the current token.
 *	pattern:	the pattern of the command.
 *
 *	Return: SUCCESS (1) / FAIL (0).
 */
static int	special_parse_pattern(char **input, int *i, char **pattern)
{
	size_t		size;
	int			j;

	size = 0;
	j = *i;
	if (input[j + 1] == NULL || is_redirect(input[j + 1]))
		return (SUCCESS);
	if (ft_strchr(input[j + 1], '\"') != NULL)
	{
		(*i)++;
		if (parse_string(input, i, pattern) == FAIL)
			return (FAIL);
		return (SUCCESS);
	}
	size = ft_strlen(input[j + 1]);
	*pattern = ft_calloc((size + 1), sizeof(char));
	if (*pattern == NULL)
		return (FAIL);
	ft_strlcpy(*pattern, input[j + 1], size + 1);
	(*i)++;
	return (SUCCESS);
}

/*	Parse the options of the command.
 *
 *	input:		the user input.
 *	i:			the index of the current token.
 *	options:	the options of the command.
 *
 *	Return: SUCCESS (1) / FAIL (0).
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

/*	Get the pattern of the command.
 *
 *	input:		the user input.
 *	i:			the index of the current token.
 *	pattern:	the pattern of the command.
 *
 *	Return: the new pattern.
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

/*	Check if the command supports options.
 *
 *	command: the command to be checked.
 *
 * 	Return: true (1) / false (0).
 */
static bool	options_possible(char *command)
{
	if (ft_strncmp(command, "exit", 5) == 0)
		return (false);
	return (true);
}

/*	Parse the command and its options.
 *
 *	input:	the user input.
 *	cmds:	the linked list of commands.
 *	i:		the index of the current token.
 *
 *	Return: SUCCESS (1) / FAIL (0).
 */
int	parse_command(char **input, t_command **cmds, int *i)
{
	t_command	*new_cmd;
	char		*options;
	char		*command;
	char		*pattern;

	command = input[*i];
	options = NULL;
	pattern = NULL;
	if (options_possible(command))
		if (parse_options(input, i, &options) == FAIL)
			return (FAIL);
	if (is_special(command))
		if (special_parse_pattern(input, i, &pattern) == FAIL)
			return (FAIL);
	new_cmd = cmd_new(command, options);
	if (options != NULL)
		free(options);
	if (new_cmd == NULL)
		return (FAIL);
	if (input[*i + 1] != NULL && !is_command(input[*i + 1])
		&& !is_redirect(input[*i + 1]))
		pattern = get_pattern(input, i, pattern);
	new_cmd->pattern = pattern;
	cmd_add_back(cmds, new_cmd);
	return (SUCCESS);
}
