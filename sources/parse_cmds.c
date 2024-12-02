/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:46:46 by nmattos-          #+#    #+#             */
/*   Updated: 2024/12/02 16:53:20 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"

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
