/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:18:33 by iriadyns          #+#    #+#             */
/*   Updated: 2025/03/24 15:01:14 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static bool	too_many_args(char *str);

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

/**
 * @brief Changes the current directory to the specified path.
 *
 * @param env_list The environment list.
 *
 * @param command The cd command structure.
 *
 * @return 0 on success, non-zero on failure.
 */
int	cd(t_env *env_list, t_command *command, t_shell *shell)
{
	int		exit_code;
	char	*path;
	char	*trimmed_path;

	path = command->pattern;
	if (!path)
		return (cd_home(env_list));
	trimmed_path = ft_strdup(path);
	if (!trimmed_path)
		return (FAIL);
	if (prepare_arg(env_list, &trimmed_path, shell) == FAIL)
		return (free(trimmed_path), FAIL);
	if (check_option(trimmed_path) == 1)
		return (free(trimmed_path), FAIL);
	exit_code = chdir(trimmed_path);
	if (too_many_args(command->pattern))
		shell->exit_status = 1;
	else if (exit_code < 0)
	{
		fprintf(stderr, "cd: %s: No such file or directory\n", trimmed_path);
		shell->exit_status = 1;
	}
	free(trimmed_path);
	return (change_pwd(env_list));
}

static bool	too_many_args(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
			i = quote_length(str, i);
		if (str[i] == ' ')
		{
			ft_putstr_fd("bash: cd: too many arguments\n", 2);
			return (true);
		}
		i++;
	}
	return (false);
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
