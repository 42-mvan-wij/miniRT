/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 15:11:57 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/08/30 12:07:42 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "structs.h"

void		render_frame(t_rt_data *rt_data);
t_vec3		vec3(long double x, long double y, long double z);
t_matrix	matrix_from_vecs(t_vec3 right, t_vec3 up, t_vec3 in);
t_matrix	matrix_dot(t_matrix m1, t_matrix m2);
t_matrix	compose(t_matrix m1, t_matrix m2);
t_vec3		transform(t_vec3 v, t_matrix m);
t_vec3		scale(t_vec3 v, long double scalar);
t_vec3		add(t_vec3 v1, t_vec3 v2);
t_vec3		normalize(t_vec3 v);
t_vec3		cross(t_vec3 v1, t_vec3 v2);
t_vec3		rot(t_vec3 v, t_vec3 axis, long double angle);

#endif
