/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/01 14:27:18 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/09/14 10:14:09 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECT_H
# define INTERSECT_H

# include "structs.h"

bool		intersect_sphere_comp(t_ray ray, t_vec3 origin, long double radius,
				long double t[2]);
void		intersect_sphere(t_ray ray, t_rayhit *best_hit, t_object *shape,
				t_vec3 *ignore_normal);
void		intersect_plane(t_ray ray, t_rayhit *best_hit, t_object *shape,
				t_vec3 *ignore_normal);
t_vec3		get_cylinder_normal(t_ray ray, t_cylinder *cylinder, long double t);
t_ray		in_cylinder_perspective(t_ray ray, t_cylinder *cylinder);
void		intersect_cylinder(t_ray ray, t_rayhit *best_hit, t_object *shape,
				t_vec3 *ignore_normal);
void		init_rayhit(t_rayhit *rayhit);
void		intersect(t_ray ray, t_rayhit *best_hit, t_object *shape,
				t_vec3 *ignore_normal);
t_rayhit	trace(t_ray ray, t_shape_list *shapes, t_rayhit *ignore);

#endif
