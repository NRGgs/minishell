/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:13:07 by iriadyns          #+#    #+#             */
/*   Updated: 2024/12/20 12:56:11 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

int pwd(char **argv)
{
	char *cwd;

	if (*(argv + 1) && check_option(*(argv + 1)) == 1)
	{
		fprintf(stderr, "pwd: invalid option -- '%s'\n", *(argv + 1));
		return 1;
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return 1;
	}
	printf("%s\n", cwd);
	free(cwd);
	return 0;
}
