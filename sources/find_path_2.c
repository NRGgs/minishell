/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:39:20 by iriadyns          #+#    #+#             */
/*   Updated: 2025/02/10 13:14:42 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	f_error(void)
{
	ft_putstr_fd("Error: Command not found.\n", 2);
	g_exit_status = CMD_NOT_FOUND;
}

char	*check_argv_executable(char *argv)
{
	if (ft_strchr(argv, '/') != NULL)
	{
		if (access(argv, X_OK) == 0)
			return (argv);
		else
			f_error();
		return (NULL);
	}
	return (NULL);
}

char	**split_paths(char **env)
{
	char	*tmp_path;

	tmp_path = path_finder(env);
	return (ft_split(tmp_path, ':'));
}

char	**split_args(char *argv)
{
	return (ft_split(argv, ' '));
}

char	*search_in_paths(char **res_split, char **args)
{
	int		i;
	char	*found;

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
	f_error();
	return (NULL);
}
