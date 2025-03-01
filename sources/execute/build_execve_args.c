/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   build_execve_args.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmattos- <nmattos-@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/17 13:25:30 by iriadyns      #+#    #+#                 */
/*   Updated: 2025/03/01 17:06:55 by nmattos       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	copy_tokens(char **src, char **dest, int *j)
{
	int	i;

	i = 0;
	while (src && src[i])
	{
		dest[(*j)++] = ft_strdup(src[i]);
		i++;
	}
}

static char	**get_args(char *str, t_env *env_list, t_shell *shell)
{
	if (!str)
		return (NULL);
	return (split_args_with_prepare(str, env_list, shell));
}

static void	free_all(char **a, char **b, char **c)
{
	free_2d_array(a);
	free_2d_array(b);
	free_2d_array(c);
}

static char	**combine_tokens(char **args_cmd, char **args_opt, char **args_pat)
{
	int		total;
	int		j;
	char	**result;

	total = count_tokens(args_cmd);
	total = total + count_tokens(args_opt);
	total = total + count_tokens(args_pat);
	result = malloc(sizeof(char *) * (total + 1));
	if (!result)
	{
		free_all(args_cmd, args_opt, args_pat);
		return (NULL);
	}
	j = 0;
	copy_tokens(args_cmd, result, &j);
	copy_tokens(args_opt, result, &j);
	copy_tokens(args_pat, result, &j);
	result[j] = NULL;
	free_all(args_cmd, args_opt, args_pat);
	return (result);
}

char	**build_execve_args(t_command *command, t_shell *shell)
{
	char	**args_cmd;
	char	**args_opt;
	char	**args_pat;

	args_cmd = get_args(command->command, command->env_list, shell);
	args_opt = get_args(command->options, command->env_list, shell);
	args_pat = get_args(command->pattern, command->env_list, shell);
	return (combine_tokens(args_cmd, args_opt, args_pat));
}
