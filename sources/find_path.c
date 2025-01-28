/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:07:33 by iriadyns          #+#    #+#             */
/*   Updated: 2025/01/28 13:16:35 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	*find_path(char *command, char **env)
{
	if (!command)
		return (NULL);
	if (command[0] == '/')
	{
		if (access(command, F_OK) == 0)
			return (command);
		else
			return (NULL);
	}
	return (true_path(command, env));
}

char	*true_path(char *argv, char **env)
{
	char	*check_exec;
	char	**res_split;
	char	**args;

	check_exec = check_argv_executable(argv);
	if (check_exec)
		return (check_exec);
	res_split = split_paths(env);
	args = split_args(argv);
	return (search_in_paths(res_split, args));
}
