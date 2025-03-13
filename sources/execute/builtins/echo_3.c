/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iriadyns <iriadyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:39:07 by iriadyns          #+#    #+#             */
/*   Updated: 2025/03/13 12:39:26 by iriadyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	compute_total_length(char **tokens, int start_index)
{
	int	total_len;
	int	i;

	total_len = 0;
	i = start_index;
	while (tokens[i])
	{
		total_len += ft_strlen(tokens[i]);
		i++;
		if (tokens[i])
			total_len++;
	}
	return (total_len);
}
