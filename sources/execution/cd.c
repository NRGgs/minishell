/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:57:49 by iriadyns          #+#    #+#             */
/*   Updated: 2024/12/01 16:58:39 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int change_pwd(t_env *env_list)
{
	char *tmp;
	t_env *pwd;

	pwd = get_env(env_list, "PWD");
	if (!pwd)
	{
		perror("Error: PWD not found");
		return 1;
	}

	tmp = pwd->value;
	pwd->value = getcwd(NULL, 0);
	if (!pwd->value)
	{
		perror("getcwd");
		return 1;
	}

	if (tmp)
		free(tmp);
	return 0;
}

int cd_home(t_env *env_list)
{
	t_env *ptr;
	char *home;
	int exit_code;

	exit_code = change_pwd(env_list);
	if (exit_code != 0)
		return exit_code;

	ptr = get_env(env_list, "HOME");
	if (!ptr)
	{
		perror("Error: HOME not found");
		return 1;
	}

	home = ptr->value;
	exit_code = chdir(home);
	if (exit_code < 0)
	{
		perror("chdir");
		return 1;
	}
	return change_pwd(env_list);
}
// TODO change fprintf to printf
int cd(t_env *env_list, char **argv)
{
	int exit_code;

	exit_code = change_pwd(env_list);
	if (exit_code != 0)
		return exit_code;

	if (!*(argv + 1))
		return cd_home(env_list);

	if (check_option(*(argv + 1)) == 1)
	{
		fprintf(stderr, "cd: invalid option -- '%s'\n", *(argv + 1));
		return 1;
	}

	exit_code = chdir(*(argv + 1));
	if (exit_code < 0)
	{
		perror("chdir");
		return 1;
	}
	return change_pwd(env_list);
}

t_env *get_env(t_env *env_list, char *identifier)
{
	t_env *ptr;
	unsigned int len;

	ptr = env_list;
	len = strlen(identifier);
	while (ptr)
	{
		if (ft_strlen(ptr->name) == len && ft_strncmp(identifier, ptr->name, len) == 0)
			return ptr;
		ptr = ptr->next;
	}
	return NULL;
}

int	check_option(char *argv)
{
	int	exit_code;

	exit_code = 0;
	if (*argv == '-')
		exit_code = 1;
	return (exit_code);
}
