/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:18:33 by iriadyns          #+#    #+#             */
/*   Updated: 2025/02/21 11:55:36 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * @brief Updates the PWD environment variable after a directory change.
 *
 * @param env_list The environment list.
 *
 * @return 0 on success, non-zero on failure.
 */
int	change_pwd(t_env *env_list)
{
	char	*tmp;
	char	*pwd;
	char	*new_pwd;

	(void)env_list;
	pwd = getenv("PWD");
	if (!pwd)
		return (perror("Error: PWD not found"), 1);
	tmp = ft_strdup(pwd);
	if (!tmp)
		return (perror("strdup"), 1);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (free(tmp), 1);
	if (setenv("PWD", new_pwd, 1) < 0)
	{
		free(new_pwd);
		free(tmp);
		return (perror("setenv"), 1);
	}
	free(new_pwd);
	free(tmp);
	return (0);
}

/**
 * @brief Changes the current directory to HOME.
 *
 * @param env_list The environment list.
 *
 * @return 0 on success, non-zero on failure.
 */
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

static char	*trim_quotes(const char *str)
{
	size_t	len;
	char	*res;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len >= 2)
	{
		if ((str[0] == '"' && str[len - 1] == '"')
			|| (str[0] == '\'' && str[len - 1] == '\''))
		{
			res = ft_strndup(str + 1, len - 2);
			return (res);
		}
	}
	return (ft_strdup(str));
}

/**
 * @brief Changes the current directory to the specified path.
 *
 * @param env_list The environment list.
 *
 * @param command The cd command structure.
 *
 * @return 0 on success, non-zero on failure.
 */
int	cd(t_env *env_list, t_command *command)
{
	int		exit_code;
	char	*path;
	char	*trimmed_path;

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
	}
	trimmed_path = trim_quotes(path);
	exit_code = chdir(trimmed_path);
	if (exit_code < 0)
	{
		fprintf(stderr, "cd: %s: No such file or directory\n", path);
		g_exit_status = 1;
	}
	free(trimmed_path);
	return (change_pwd(env_list));
}

/**
 * @brief Checks if the given argument is an invalid option.
 *
 * @param argv The argument string.
 *
 * @return 1 if invalid option, 0 otherwise.
 */
int	check_option(char *argv)
{
	if (*argv == '-')
	{
		ft_putstr_fd("DEBUG: Invalid option detected\n", 2);
		return (1);
	}
	return (0);
}
