/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:29:55 by iriadyns          #+#    #+#             */
/*   Updated: 2025/03/13 12:38:29 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	process_echo_options(char **args, int *start_index)
{
	int	flag;
	int	i;
	int	j;

	i = 0;
	flag = 0;
	while (args[i])
	{
		if (ft_strncmp(args[i], "-n", 2) == 0)
		{
			j = 1;
			while (args[i][j] && args[i][j] == 'n')
				j++;
			if (args[i][j] == '\0')
			{
				flag = 1;
				i++;
				continue ;
			}
		}
		break ;
	}
	*start_index = i;
	return (flag);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static char	*get_opt_output(char *options, int *flag)
{
	char	**args;
	int		start_index;
	char	*opt_output;

	*flag = 0;
	if (!options || options[0] == '\0')
		return (NULL);
	args = ft_split(options, ' ');
	if (!args)
		return (NULL);
	*flag = process_echo_options(args, &start_index);
	opt_output = join_tokens(args, start_index);
	free_split(args);
	return (opt_output);
}

static char	*get_final_output(char *pattern, char *opt_output)
{
	char	*final_output;
	char	*tmp;

	if (pattern && pattern[0] != '\0')
	{
		if (opt_output && opt_output[0] != '\0')
		{
			tmp = join_with_space(opt_output, pattern);
			free(opt_output);
			final_output = tmp;
		}
		else
		{
			if (opt_output)
				free(opt_output);
			final_output = ft_strdup(pattern);
		}
	}
	else
		final_output = opt_output;
	return (final_output);
}

int	echo(t_command *command, t_shell *shell)
{
	int		flag;
	char	*opt_output;
	char	*final_output;

	if (!command)
		return (1);
	if ((!command->options || command->options[0] == '\0')
		&& (!command->pattern || command->pattern[0] == '\0'))
		return (ft_putstr_fd("\n", STDOUT_FILENO), 0);
	flag = 0;
	opt_output = get_opt_output(command->options, &flag);
	final_output = get_final_output(command->pattern, opt_output);
	if (!final_output)
		return (1);
	ft_putstr_fd(final_output, STDOUT_FILENO);
	free(final_output);
	if (!flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
	(void)shell;
	return (0);
}
