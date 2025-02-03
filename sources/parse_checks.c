/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:04:52 by nmattos-          #+#    #+#             */
/*   Updated: 2025/02/03 14:14:00 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*	Check if the command is a command with string input
 *
 *	command: the command to be checked.
 *
 * 	Return: true (1) / false (0).
 */
bool	is_special(char *command)
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
bool	is_redirect(char *str)
{
	if (ft_strcmp(str, ">") == 0 || ft_strcmp(str, ">>") == 0
		|| ft_strcmp(str, "<") == 0 || ft_strcmp(str, "<<") == 0
		|| ft_strcmp(str, "|") == 0)
	{
		return (true);
	}
	return (false);
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

/*	Check if the command supports options.
 *
 *	command: the command to be checked.
 *
 * 	Return: true (1) / false (0).
 */
bool	options_possible(char *command)
{
	if (ft_strncmp(command, "exit", 5) == 0)
		return (false);
	return (true);
}

/*	Check all paths in the PATH environment variable for the command.
 *
 *	cmd:	the command to be checked.
 *	path:	the PATH environment variable.
 *
 * 	Return: SUCCESS (1) / FAIL (0).
 */
int	check_path(char *cmd, char *path)
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
