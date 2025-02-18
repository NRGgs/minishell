/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:04:52 by nmattos-          #+#    #+#             */
/*   Updated: 2025/02/18 11:05:23 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Check if the command is a command with string input.
 *
 * @param command The command to be checked.
 * @return true if the command is a special command, false otherwise.
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

/**
 * @brief Check if the string is a redirect.
 *
 * @param str The string to be checked.
 * @return true if the string is a redirect, false otherwise.
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

/**
 * @brief Check if the command is a built-in command.
 *
 * @param cmd The command to be checked.
 * @return SUCCESS (1) if the command is found, FAIL (0) if not found,
 * ERROR (-1) on error.
 */
int	is_command(char *cmd)
{
	char	*path_env;
	char	*path;
	int		found;

	if (ft_strncmp(cmd, ".", 2) == 0 || ft_strncmp(cmd, "..", 3) == 0)
		return (FAIL);
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

/**
 * @brief Check if the command supports options.
 *
 * @param command The command to be checked.
 * @return true if the command supports options, false otherwise.
 */
bool	options_possible(char *command)
{
	if (ft_strncmp(command, "exit", 5) == 0)
		return (false);
	return (true);
}

/**
 * @brief Check all paths in the PATH environment variable for the command.
 *
 * @param cmd The command to be checked.
 * @param path The PATH environment variable.
 * @return SUCCESS (1) if the command is found, FAIL (0) if not found.
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
