/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmattos- <nmattos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:55:09 by nmattos-          #+#    #+#             */
/*   Updated: 2024/11/25 09:15:12 by nmattos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_flags
{
	int		minus;
	int		zero;
	int		precision;
	int		alternate;
	int		space;
	int		sign;
	int		fieldwidth;
	int		printed;
}	t_flags;

int		ft_printf(const char *str, ...);

t_flags	*init_flag_struct(void);
char	*get_flags(t_flags *flags, char *format);
void	reset_flags(t_flags *flags);

void	add_spaces(t_flags *flags, int spaces);
void	add_zeros(t_flags *flags, int zeros);

void	print_char(t_flags *flags, int c);
void	print_string(t_flags *flags, char *str);

void	print_decimal(t_flags *flags, int n);
void	d_putnbr(t_flags *flags, int n);
void	d_print_sign(t_flags *flags, int n);
void	d_print_precision_right(t_flags *flags, int n, int length);
void	d_print_precision_left(t_flags *flags, int n, int length);
void	d_print_zero_right(t_flags *flags, int n, int length);
void	d_print_left(t_flags *flags, int n, int length);
void	d_print_number(t_flags *flags, int n, int length);

void	print_unsigned(t_flags *flags, unsigned int n);
void	u_putnbr(t_flags *flags, unsigned int n);
void	u_print_precision_right(t_flags *flags, int n, int length);
void	u_print_precision_left(t_flags *flags, int n, int length);
void	u_print_zero_right(t_flags *flags, int n, int length);
void	u_print_left(t_flags *flags, int n, int length);
void	u_print_number(t_flags *flags, int n, int length);

void	print_hex(t_flags *flags, unsigned int n, char format);
void	h_putnbr(t_flags *flags, unsigned int arg, char format);
void	add_prefix(t_flags *flags, char format);
void	h_print_precision_right(t_flags *flags, unsigned int n,
			int length, char format);
void	h_print_precision_left(t_flags *flags, unsigned int n,
			int length, char format);
void	h_print_zero_right(t_flags *flags, unsigned int n,
			int length, char format);
void	h_print_left(t_flags *flags, unsigned int n,
			int length, char format);
void	h_print_number(t_flags *flags, unsigned int n,
			int length, char format);

void	print_pointer(t_flags *flags, void *arg);

#endif
