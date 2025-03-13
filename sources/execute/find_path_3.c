/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:49:32 by iriadyns          #+#    #+#             */
/*   Updated: 2025/03/13 16:14:30 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	replace_marker_with_space(char **result)
{
	int	i;
	int	j;

	i = 0;
	while (result && result[i])
	{
		j = 0;
		while (result[i][j])
		{
			if (result[i][j] == '\001')
				result[i][j] = ' ';
			j++;
		}
		i++;
	}
}

static char	**process_quotes_split(char *dup)
{
	char	*processed;
	char	**result;

	processed = handle_double_spaces(dup);
	free(dup);
	if (!processed)
		return (NULL);
	result = special_split(processed, ' ');
	free(processed);
	if (result)
		replace_marker_with_space(result);
	return (result);
}

char	**split_args_with_prepare(char *argv, t_env *env_list, t_shell *shell)
{
	char	*dup;
	char	**result;

	dup = ft_strdup(argv);
	if (!dup)
		return (NULL);
	if (prepare_arg(env_list, &dup, shell) == FAIL)
	{
		free(dup);
		return (NULL);
	}
	if (ft_strchr(argv, '\'') || ft_strchr(argv, '\"'))
		result = process_quotes_split(dup);
	else
	{
		result = ft_split(dup, ' ');
		free(dup);
	}
	return (result);
}
