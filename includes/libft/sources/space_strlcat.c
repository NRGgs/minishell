/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_strlcat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:09:44 by nmattos-          #+#    #+#             */
/*   Updated: 2025/02/03 14:10:31 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	space_strlcat(char *dst, char *src, size_t size)
{
	ft_strlcat(dst, " ", size);
	ft_strlcat(dst, src, size);
}
