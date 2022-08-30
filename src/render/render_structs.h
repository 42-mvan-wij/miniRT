/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_structs.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 15:06:29 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/08/30 11:38:02 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_STRUCTS_H
# define RENDER_STRUCTS_H

# include "MLX42.h"
# include "input/input_structs.h"

typedef struct s_matrix {
	long double	data[3 * 3];
}	t_matrix;

#endif
