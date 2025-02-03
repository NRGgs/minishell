/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_newline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:10:45 by nmattos-          #+#    #+#             */
/*   Updated: 2025/02/03 14:11:27 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*add_newline(char *input)
{
	char	*temp;

	if (input[0] == '\0')
		return (input);
	temp = ft_strjoin(input, "\n");
	if (temp == NULL)
	{
		free(input);
		return (NULL);
	}
	free(input);
	input = ft_strdup(temp);
	free(temp);
	return (input);
}
