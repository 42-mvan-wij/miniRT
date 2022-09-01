/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec3_structs.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/01 14:15:56 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/09/01 14:16:58 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_STRUCTS_H
# define VEC3_STRUCTS_H

typedef struct s_vec3 {
	long double	x;
	long double	y;
	long double	z;
}	t_vec3;

typedef struct s_matrix {
	long double	data[3 * 3];
}	t_matrix;

#endif
