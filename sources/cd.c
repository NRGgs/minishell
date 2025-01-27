/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:18:33 by iriadyns          #+#    #+#             */
/*   Updated: 2025/01/27 14:33:13 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	change_pwd(t_env *env_list)
{
	char	*tmp;
	char	*pwd;

	(void)env_list;
	pwd = getenv("PWD");
	if (!pwd)
	{
		perror("Error: PWD not found");
		return (1);
	}
	tmp = ft_strdup(pwd);
	if (!tmp)
	{
		perror("strdup");
		return (1);
	}
	if (setenv("PWD", getcwd(NULL, 0), 1) < 0)
	{
		perror("setenv");
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

int	cd_home(t_env *env_list)
{
	char	*home;

	(void)env_list;
	home = getenv("HOME");
	if (!home)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (1);
	}
	if (chdir(home) < 0)
	{
		perror("cd");
		return (1);
	}
	return (change_pwd(env_list));
}

int	cd(t_env *env_list, t_command *command)
{
	int		exit_code;
	char	*path;

	(void)env_list;
	path = command->pattern;
	if (!path)
	{
		ft_putstr_fd("DEBUG: No path provided, going to HOME\n", 2);
		return (cd_home(env_list));
	}
	if (check_option(path) == 1)
	{
		fprintf(stderr, "cd: invalid option -- '%s'\n", path);
		return (1);
	}
	exit_code = chdir(path);
	if (exit_code < 0)
	{
		fprintf(stderr, "cd: %s: No such file or directory\n", path);
		g_exit_status = 1;
		return (1);
	}
	return (change_pwd(env_list));
}

int	check_option(char *argv)
{
	if (*argv == '-')
	{
		ft_putstr_fd("DEBUG: Invalid option detected\n", 2);
		return (1);
	}
	return (0);
}
