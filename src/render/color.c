/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/01 14:04:26 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/09/14 10:34:29 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "structs.h"
#include "utils/utils.h"
#include "render/intersect/intersect.h"
#include "vec3/vec3.h"
#include "render/render.h"

t_vec3	get_shape_color(t_object *shape)
{
	if (shape->type == SPHERE)
		return (color2vec(shape->sphere.rgba));
	if (shape->type == PLANE)
		return (color2vec(shape->plane.rgba));
	if (shape->type == CYLINDER)
		return (color2vec(shape->cylinder.rgba));
	return (vec3(0, 0, 0));
}

t_vec3	adjust_color(t_vec3 color, t_rayhit hit, t_ray ray, t_rt_data *rt_data)
{
	t_ray		light_ray;
	t_vec3		diff;
	t_rayhit	new_hit;
	long double	cos_a;
	long double	mattness;
	t_vec3		effect;

	if (hit.distance >= INFINITY)
		return (color);
	color = add(color, scale(scale_color(color2vec(rt_data->scene.ambient.rgba), get_shape_color(hit.shape)), rt_data->scene.ambient.brightness));
	light_ray.origin = add(ray.origin, scale(ray.dir, hit.distance));
	diff = sub(rt_data->scene.light.pos, light_ray.origin);
	light_ray.dir = normalize(diff);
	new_hit = trace(light_ray, rt_data->scene.objects, &hit);
	if (new_hit.distance * new_hit.distance >= mag2(diff))
	{
		cos_a = dot(light_ray.dir, hit.vis_normal);
		if (cos_a <= 0)
			return (color);
		effect = scale(scale(color2vec(rt_data->scene.light.rgba), cos_a), 1.0 / (mag(diff) + hit.distance) * (mag(diff) + hit.distance));
		mattness = 1; // kappa * dot(normal, ray.dir);
		// glossyness;
		color = add(color,
			scale(scale_color(
				scale(effect, mattness), get_shape_color(hit.shape)
			), rt_data->scene.light.brightness)
		);
	}
	return (color);
}

t_color	get_pixel_color(t_rt_data *rt_data, int x, int y)
{
	t_vec3		color;
	int			i;
	t_ray		ray;
	t_rayhit	hit;

	set_ray(&ray, x, y, rt_data);
	color = vec3(0, 0, 0);
	i = 0;
	// while (i < MAX_BOUNCES)
	{
		hit = trace(ray, rt_data->scene.objects, NULL);
		// color = vec3(fabsl(hit.normal.x), fabsl(hit.normal.y), fabsl(hit.normal.z));
		color = adjust_color(color, hit, ray, rt_data);
		i++;
	}
	return (vec2color(color));
}
