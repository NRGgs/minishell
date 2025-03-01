/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:39:20 by iriadyns          #+#    #+#             */
/*   Updated: 2025/03/01 16:16:21 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Checks if an absolute command path is executable.
 * If the path contains a '/', checks if it is a directory or executable.
 *
 * @param argv The command path.
 *
 * @return A duplicated string if executable, or NULL.
 */
char	*check_argv_executable(char *argv, t_shell *shell)
{
	struct stat	st;

	if (ft_strchr(argv, '/') != NULL)
	{
		if (stat(argv, &st) == 0 && S_ISDIR(st.st_mode))
		{
			ft_putstr_fd(argv, 2);
			ft_putstr_fd(": Is a directory\n", 2);
			shell->exit_status = CMD_NOT_FOUND;
			return (NULL);
		}
		if (access(argv, X_OK) == 0)
			return (ft_strdup(argv));
		else
			shell->exit_status = CMD_NOT_FOUND;
		return (NULL);
	}
	return (NULL);
}

/**
 * @brief Prints an error message for a command not found.
 */
void	f_error(t_shell *shell)
{
	ft_putstr_fd("Error: Command not found.\n", 2);
	shell->exit_status = CMD_NOT_FOUND;
}

char	**split_args_with_prepare(char *argv, t_env *env_list)
{
	char	*dup;
	char	**result;

	dup = ft_strdup(argv);
	if (!dup)
		return (NULL);
	if (prepare_arg(env_list, &dup) == FAIL)
	{
		free(dup);
		return (NULL);
	}
	result = ft_split(dup, ' ');
	free(dup);
	return (result);
}

char	**split_paths_env(t_env *env_list)
{
	t_env	*var;
	char	**paths;

	var = find_env_var(env_list, "PATH");
	if (!var || !var->value)
		return (NULL);
	paths = ft_split(var->value, ':');
	return (paths);
}

/**
 * @brief Searches for an executable in the provided directories.
 * Appends the command to each directory (using fn_path)
 * and checks for executability.
 *
 * @param res_split The array of directory paths.
 *
 * @param args An array whose first element is the command.
 *
 * @return A duplicated full path if found, or NULL.
 */
char	*search_in_paths(char **res_split, char **args, t_shell *shell)
{
	int		i;
	char	*found;

	if (!args || !args[0] || args[0][0] == '\0')
	{
		free_2d_array(res_split);
		free_2d_array(args);
		f_error(shell);
		return (NULL);
	}
	fn_path(res_split, args[0]);
	i = 0;
	while (res_split[i])
	{
		if (access(res_split[i], X_OK) == 0)
		{
			found = ft_strdup(res_split[i]);
			free_2d_array(res_split);
			free_2d_array(args);
			return (found);
		}
		i++;
	}
	free_2d_array(res_split);
	free_2d_array(args);
	f_error(shell);
	return (NULL);
}
