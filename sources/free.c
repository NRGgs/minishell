/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:40:40 by nmattos-          #+#    #+#             */
/*   Updated: 2025/02/05 15:45:34 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_null(void **ptr)
{
	if (ptr != NULL || *ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}
