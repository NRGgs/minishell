/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:18:33 by iriadyns          #+#    #+#             */
/*   Updated: 2025/01/07 10:28:28 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	change_pwd(t_env *env_list)
// {
// 	char	*tmp;
// 	t_env	*pwd;

// 	pwd = get_env(env_list, "PWD");
// 	if (!pwd)
// 	{
// 		perror("Error: PWD not found");
// 		return 1;
// 	}
// 	tmp = pwd->value;
// 	pwd->value = getcwd(NULL, 0);
// 	if (!pwd->value)
// 	{
// 		perror("getcwd");
// 		return 1;
// 	}
// 	if (tmp)
// 		free(tmp);
// 	return 0;
// }

// int	cd_home(t_env *env_list)
// {
//     t_env	*ptr;
//     char	*home;

//     ptr = get_env(env_list, "HOME");
//     if (!ptr) {
//         ft_putstr_fd("DEBUG: HOME not found in get_env\n", 2);
//         return 1;
//     }
//     home = ptr->value;
//     if (!home) {
//         ft_putstr_fd("DEBUG: HOME is NULL\n", 2);
//         return 1;
//     }
//     ft_putstr_fd("DEBUG: HOME value: ", 2);
//     ft_putstr_fd(home, 2);
//     ft_putstr_fd("\n", 2);
//     if (chdir(home) < 0)
//     {
//         perror("cd");
//         return 1;
//     }
//     return change_pwd(env_list);
// }


// int	cd(t_env *env_list, char **argv)
// {
// 	int		exit_code;

// 	if (!argv[1]) // Если аргументов нет, вызываем cd_home
// 		return cd_home(env_list);

// 	if (check_option(argv[1]) == 1) // Проверяем на опции
// 	{
// 		fprintf(stderr, "cd: invalid option -- '%s'\n", argv[1]);
// 		return 1;
// 	}

// 	exit_code = chdir(argv[1]); // Переходим в директорию
// 	if (exit_code < 0)
// 	{
// 		perror("cd");
// 		return 1;
// 	}
// 	return change_pwd(env_list); // Обновляем PWD
// }

// t_env	*get_env(t_env *env_list, char *identifier)
// {
// 	t_env	*ptr;
// 	size_t	len;

// 	if (!env_list || !identifier)
// 		return NULL;
// 	ptr = env_list;
// 	len = ft_strlen(identifier);
// 	while (ptr)
// 	{
// 		if (ft_strlen(ptr->name) == len && ft_strncmp(identifier, ptr->name, len) == 0)
// 			return ptr;
// 		ptr = ptr->next;
// 	}
// 	return NULL;
// }


// int	check_option(char *argv)
// {
// 	if (*argv == '-')
// 		return 1;
// 	return 0;
// }
int	change_pwd(t_env *env_list)
{
	char	*tmp;
	char	*pwd;

	(void)env_list; // Если env_list больше не используется, добавьте явное игнорирование.
	pwd = getenv("PWD");
	if (!pwd)
	{
		perror("Error: PWD not found");
		return 1;
	}
	tmp = strdup(pwd);
	if (!tmp)
	{
		perror("strdup");
		return 1;
	}
	if (setenv("PWD", getcwd(NULL, 0), 1) < 0)
	{
		perror("setenv");
		free(tmp);
		return 1;
	}
	free(tmp);
	return 0;
}

int	cd_home(t_env *env_list)
{
	char	*home;

	(void)env_list; // Если env_list больше не используется, добавьте явное игнорирование.
	home = getenv("HOME");
	if (!home)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return 1;
	}
	if (chdir(home) < 0)
	{
		perror("cd");
		return 1;
	}
	return change_pwd(env_list);
}

int	cd(t_env *env_list, t_command *command)
{
	int		exit_code;
	char	*path;

	(void)env_list; // Если env_list больше не используется, игнорируем его.

	// Получаем путь из commands->options
	path = command->options;
	if (!path)
	{
		ft_putstr_fd("DEBUG: No path provided, going to HOME\n", 2);
		return cd_home(env_list);
	}
	if (check_option(path) == 1) // Проверяем на опции
	{
		fprintf(stderr, "cd: invalid option -- '%s'\n", path);
		return 1;
	}
	exit_code = chdir(path);
	if (exit_code < 0)
	{
		perror("cd");
		return 1;
	}
	return change_pwd(env_list);
}


int	check_option(char *argv)
{
	// Проверяем, начинается ли аргумент с "-"
	if (*argv == '-')
	{
		ft_putstr_fd("DEBUG: Invalid option detected\n", 2);
		return 1;
	}
	return 0;
}
