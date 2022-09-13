/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_structs.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 15:06:29 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/09/05 11:12:24 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_STRUCTS_H
# define RENDER_STRUCTS_H

# include "vec3/vec3_structs.h"
# include "input/input_structs.h"

typedef struct s_ray {
	t_vec3	dir;
	t_vec3	origin;
	t_vec3	rgb_energy;
}	t_ray;

typedef struct s_rayhit {
	long double		distance;
	t_vec3			normal;
	t_vec3			vis_normal;
	t_object		*shape;
}	t_rayhit;

#endif
