/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:07:33 by iriadyns          #+#    #+#             */
/*   Updated: 2025/01/27 14:14:58 by nmattos-         ###   ########.fr       */
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

char	*true_path(char *argv, char **env)
{
	int		i;
	char	**res_split;
	char	**args;
	char	*path;

	if (access(argv, F_OK) == 0)
		return (argv);
	if (ft_strchr(argv, '/') != NULL)
		f_error();
	path = "PATH=";
	i = 0;
	args = ft_split(argv, ' ');
	path = path_finder(env);
	i = 0;
	res_split = ft_split(path, ':');
	fn_path(res_split, args[0]);
	while (res_split[i])
	{
		if (access(res_split[i], F_OK) == 0)
			return (res_split[i]);
		i++;
	}
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

