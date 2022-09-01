/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 15:11:57 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/09/01 14:44:35 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "structs.h"

t_vec3		get_shape_color(t_object *shape);
t_vec3		adjust_color(t_vec3 color, t_rayhit hit, t_ray ray,
				t_rt_data *rt_data);
t_color		get_pixel_color(t_rt_data *rt_data, int x, int y);

void		set_ray(t_ray *ray, long double x, long double y,
				t_rt_data *rt_data);
void		render_frame(t_rt_data *rt_data);

#endif
