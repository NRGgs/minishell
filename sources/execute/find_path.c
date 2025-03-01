/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_path.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: iriadyns <iriadyns@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/04 12:07:33 by iriadyns      #+#    #+#                 */
/*   Updated: 2025/03/01 17:06:14 by nmattos       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Appends a '/' and the command to each directory in the array.
 * Modifies each element of res_split to include the command.
 *
 * @param res_split The array of directory paths.
 *
 * @param argv The command name.
 */
void	fn_path(char **res_split, char *argv)
{
	int		i;
	char	*tmp;
	char	*new_str;

	tmp = NULL;
	new_str = NULL;
	i = 0;
	while (res_split[i])
	{
		tmp = ft_strjoin(res_split[i], "/");
		new_str = ft_strjoin(tmp, argv);
		free(res_split[i]);
		res_split[i] = new_str;
		free(tmp);
		i++;
	}
}

/**
 * @brief Finds the PATH variable in the environment.
 * Searches the environment array for the variable starting with "PATH=".
 *
 * @param env The environment array.
 *
 * @return The PATH string.
 */
char	*path_finder(char **env)
{
	int		i;
	char	*path;

	i = 0;
	path = "PATH=";
	while (env[i])
	{
		if (*env[i] == 'P')
		{
			if (!(ft_strncmp(env[i], path, 5)))
				path = env[i];
		}
		i++;
	}
	return (path);
}

/**
 * @brief Frees a NULL-terminated array of strings.
 *
 * @param arr The array to free.
 */
void	free_2d_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/**
 * @brief Determines the full path for a command.
 * If the command starts with '/', checks if it is executable; otherwise,
 * searches for the command in the PATH.
 *
 * @param command The command string.
 *
 * @param env The environment array.
 *
 * @return A duplicated string with the full path, or NULL if not found.
 */
char	*find_path(char *command, t_env *env_list, t_shell *shell)
{
	struct stat	st;

	if (!command)
		return (NULL);
	if (command[0] == '/')
	{
		if (stat(command, &st) == 0 && S_ISDIR(st.st_mode))
		{
			ft_putstr_fd(command, 2);
			ft_putstr_fd(": Is a directory\n", 2);
			shell->exit_status = CMD_NOT_FOUND;
			return (NULL);
		}
		if (access(command, X_OK) == 0)
			return (ft_strdup(command));
		else
			return (NULL);
	}
	return (true_path(command, env_list, shell));
}

/**
 * @brief Searches for a command in the PATH directories.
 *
 * @param argv The command name.
 *
 * @param env The environment array.
 *
 * @return A duplicated full path if found, or NULL.
 */
char	*true_path(char *argv, t_env *env_list, t_shell *shell)
{
	char	*check_exec;
	char	**res_split;
	char	**args;

	check_exec = check_argv_executable(argv, shell);
	if (check_exec)
		return (check_exec);
	res_split = split_paths_env(env_list);
	if (!res_split)
	{
		f_error(shell);
		return (NULL);
	}
	args = split_args_with_prepare(argv, env_list, shell);
	if (!args)
	{
		free_2d_array(res_split);
		return (NULL);
	}
	return (search_in_paths(res_split, args, shell));
}
