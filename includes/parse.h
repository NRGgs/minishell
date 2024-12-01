/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmattos <nmattos@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/01 10:44:28 by nmattos       #+#    #+#                 */
/*   Updated: 2024/12/01 12:33:26 by nmattos       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "libft/libft.h"
# include <stdbool.h>
# include <stdio.h>

# define FAIL 0
# define SUCCESS 1

typedef struct s_variable
{
	char				*name;
	char				*value;
	struct s_variable	*next;
}	t_variable;

/*****************************************************************************\
*                             Function Prototypes                             *
\*****************************************************************************/

/* parse.c */
bool	is_variable(char *str);
int		parse_variable(char *str, t_variable **vars);

/* variables.c */
t_variable	*var_new(char *name, char *value);
t_variable	*var_last(t_variable *vars);
void		var_add_back(t_variable **vars, t_variable *new_var);
t_variable	*var_find(t_variable *vars, char *name);

#endif
