/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:07:33 by iriadyns          #+#    #+#             */
/*   Updated: 2025/01/27 16:56:36 by iriadyns         ###   ########.fr       */
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

static void	free_2d_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	*true_path(char *argv, char **env)
{
	char	**res_split;
	char	**args;
	char	*tmp_path;
	char	*found;
	int		i;

	if (access(argv, F_OK) == 0)
		return (argv);
	if (ft_strchr(argv, '/') != NULL)
		f_error(); 
	tmp_path = path_finder(env);
	res_split = ft_split(tmp_path, ':');
	args = ft_split(argv, ' ');
	fn_path(res_split, args[0]);
	i = 0;
	while (res_split[i])
	{
		if (access(res_split[i], F_OK) == 0)
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
	f_error(); 
	return (NULL);
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

void	f_error(void)
{
	ft_putstr_fd("Error: Command not found.\n", 2);
	g_exit_status = CMD_NOT_FOUND;
}
