/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec3.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/01 14:06:55 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/09/01 14:35:54 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

# include "structs.h"

t_vec3		vec3(long double x, long double y, long double z);
t_vec3		scale(t_vec3 v, long double scalar);
t_vec3		add(t_vec3 v1, t_vec3 v2);
t_vec3		sub(t_vec3 v1, t_vec3 v2);
bool		vec3_eq(t_vec3 v1, t_vec3 v2);

long double	mag2(t_vec3 v);
long double	mag(t_vec3 v);
long double	dist2(t_vec3 v1, t_vec3 v2);
long double	dist(t_vec3 v1, t_vec3 v2);
t_vec3		normalize(t_vec3 v);

long double	dot(t_vec3 v1, t_vec3 v2);
t_vec3		cross(t_vec3 v1, t_vec3 v2);

t_vec3		rot(t_vec3 v, t_vec3 axis, long double angle);

t_matrix	matrix_from_vecs(t_vec3 right, t_vec3 up, t_vec3 in);
t_matrix	matrix_dot(t_matrix m1, t_matrix m2);
t_matrix	compose(t_matrix m1, t_matrix m2);
t_vec3		transform(t_vec3 v, t_matrix m);

#endif
