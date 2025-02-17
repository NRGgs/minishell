/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_execve_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:25:30 by iriadyns          #+#    #+#             */
/*   Updated: 2025/02/17 13:35:33 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_tokens(char **arr)
{
	int	count;

	count = 0;
	while (arr[count])
		count++;
	return (count);
}

static void	append_tokens(char **dst, char **src, int *i)
{
	int	j;

	j = 0;
	while (src[j])
	{
		dst[*i] = ft_strdup(src[j]);
		(*i)++;
		j++;
	}
}

static void	get_opt_and_pat(t_command *cmd, char ***opt, char ***pat, int *cnt)
{
	*cnt = 1;
	if (cmd->options)
	{
		*opt = ft_split(cmd->options, ' ');
		*cnt += count_tokens(*opt);
	}
	else
		*opt = NULL;
	if (cmd->pattern)
	{
		*pat = ft_split(cmd->pattern, ' ');
		*cnt += count_tokens(*pat);
	}
	else
		*pat = NULL;
}

char	**build_execve_args(t_command *cmd)
{
	char	**opt;
	char	**pat;
	char	**args;
	int		cnt;
	int		i;

	get_opt_and_pat(cmd, &opt, &pat, &cnt);
	args = malloc(sizeof(char *) * (cnt + 1));
	if (!args)
	{
		free_2d_array(opt);
		free_2d_array(pat);
		return (NULL);
	}
	i = 0;
	args[i++] = ft_strdup(cmd->command);
	if (opt)
		append_tokens(args, opt, &i);
	if (pat)
		append_tokens(args, pat, &i);
	args[i] = NULL;
	free_2d_array(opt);
	free_2d_array(pat);
	return (args);
}
