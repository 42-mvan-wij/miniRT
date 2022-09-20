/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 15:12:03 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/09/20 18:06:57 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include <math.h>
#include "structs.h"
#include "vec3/vec3.h"
#include "utils/utils.h"
#include "render/intersect/intersect.h"
#include "render/render.h"

void	calc_xx_yy(t_rt_data *rt_data, long double x, long double y,
			long double xx_yy[2])
{
	long double	aspect_ratio;
	long double	angle;

	aspect_ratio = (long double)rt_data->width / rt_data->height;
	angle = tanl(M_PI * 0.5 * rt_data->scene.camera.fov / 180.0);
	xx_yy[0] = (2 * ((x + 0.5) / rt_data->width) - 1) * angle * aspect_ratio;
	xx_yy[1] = (1 - 2 * ((y + 0.5) / rt_data->height)) * angle;
}

void	set_ray(t_ray *ray, long double x, long double y, t_rt_data *rt_data)
{
	long double	xx_yy[2];
	t_vec3		right;
	t_vec3		up;

	calc_xx_yy(rt_data, x, y, xx_yy);
	if (almost_equal(rt_data->scene.camera.norm.y, 1))
		right = vec3(1, 0, 0);
	else
		right = normalize(cross(vec3(0, 1, 0), rt_data->scene.camera.norm));
	up = normalize(cross(rt_data->scene.camera.norm, right));
	ray->dir = normalize(add(rt_data->scene.camera.norm, add(
					scale(up, xx_yy[1]),
					scale(right, xx_yy[0]))
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
