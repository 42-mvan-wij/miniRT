/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 15:12:03 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/09/14 10:38:16 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include <math.h>
#include "structs.h"
#include "vec3/vec3.h"
#include "utils/utils.h"
#include "render/intersect/intersect.h"
#include "render/render.h"

void	set_ray(t_ray *ray, long double x, long double y, t_rt_data *rt_data)
{
	unsigned int	width = rt_data->width;
	unsigned int	height = rt_data->height;
	long double		inv_width = 1.0 / (long double)width;
	long double		inv_height = 1.0 / (long double)height;
	long double		fov = rt_data->scene.camera.fov;
	long double		aspect_ratio = (long double)width / (long double)height;
	long double		angle = tanl(M_PI * 0.5 * fov / 180.0);

	long double		xx = (2 * ((x + 0.5) * inv_width) - 1) * angle * aspect_ratio;
	long double		yy = (1 - 2 * ((y + 0.5) * inv_height)) * angle;
	t_vec3			right;
	t_vec3			up;

	if (almost_equal(rt_data->scene.camera.norm.y, 1))
		right = vec3(1, 0, 0);
	else
		right = cross(vec3(0, 1, 0), rt_data->scene.camera.norm);
	up = cross(rt_data->scene.camera.norm, right);
	ray->dir = normalize(add(rt_data->scene.camera.norm, add(
					scale(up, yy),
					scale(right, xx))
				));
	ray->origin = rt_data->scene.camera.pos;
	ray->rgb_energy = vec3(1, 1, 1);
}

void	render_frame(t_rt_data *rt_data)
{
	int		y;
	int		x;
	t_color	color;

	y = 0;
	while (y < rt_data->height)
	{
		x = 0;
		while (x < rt_data->width)
		{
			color = get_pixel_color(rt_data, x, y);
			mlx_put_pixel(rt_data->image, x, y, color);
			x++;
		}
		y++;
	}
}
