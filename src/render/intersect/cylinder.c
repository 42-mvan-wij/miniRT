/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/01 14:01:40 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/10/20 12:53:05 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "utils/utils.h"
#include "vec3/vec3.h"
#include "render/intersect/intersect.h"
#include <math.h>

t_vec3	get_cylinder_normal(t_ray ray, t_cylinder *cylinder, long double t)
{
	t_vec3	point;
	t_vec3	dir;

	point = add(scale(ray.dir, t), ray.origin);
	dir = sub(point, cylinder->pos);
	return (normalize(cross(cross(cylinder->norm, dir), cylinder->norm)));
}

t_ray	in_cylinder_perspective(t_ray ray, t_cylinder *cylinder)
{
	t_vec3		flat_normal;
	long double	cos_sin_a[2];
	long double	cos_sin_b[2];
	t_matrix	m;
	t_ray		out_ray;

	if (almost_equal(cylinder->norm.y, 1) || almost_equal(cylinder->norm.y, -1))
	{
		ray.origin = sub(ray.origin, cylinder->pos);
		return (ray);
	}
	flat_normal = vec3(cylinder->norm.x, 0, cylinder->norm.z);
	cos_sin(vec3(1, 0, 0), flat_normal, cos_sin_a);
	cos_sin(vec3(0, 1, 0), cylinder->norm, cos_sin_b);
	m = compose(matrix_from_vecs(
				vec3(cos_sin_b[COS], cos_sin_b[SIN], 0),
				vec3(-cos_sin_b[SIN], cos_sin_b[COS], 0),
				vec3(0, 0, 1)),
			matrix_from_vecs(
				vec3(cos_sin_a[COS], 0, cos_sin_a[SIN]),
				vec3(0, 1, 0),
				vec3(-cos_sin_a[SIN], 0, cos_sin_a[COS])));
	out_ray.dir = transform(ray.dir, m);
	out_ray.origin = transform(sub(ray.origin, cylinder->pos), m);
	return (out_ray);
}

bool	intersects_vertically(t_ray pers_ray, long double t, long double height)
{
	return (pers_ray.dir.y * t + pers_ray.origin.y < -height / 2
		|| pers_ray.dir.y * t + pers_ray.origin.y > height / 2);
}

bool	get_intersect_times(t_ray pers_ray, t_cylinder cylinder,
			long double t[2])
{
	t_ray		flat_ray;
	long double	stretch_factor;

	flat_ray.origin = vec3(pers_ray.origin.x, 0, pers_ray.origin.z);
	flat_ray.dir = normalize(vec3(pers_ray.dir.x, 0, pers_ray.dir.z));
	if (!intersect_sphere_comp(flat_ray, vec3(0, 0, 0), cylinder.radius, t))
		return (false);
	stretch_factor = dot(pers_ray.dir, flat_ray.dir);
	t[0] /= stretch_factor;
	t[1] /= stretch_factor;
	return (true);
}

void	intersect_cylinder(t_ray ray, t_rayhit *best_hit, t_object *shape,
			t_vec3 *ignore_normal)
{
	t_ray		pers_ray;
	long double	t[2];
	long double	tt;
	t_vec3		normal;

	pers_ray = in_cylinder_perspective(ray, &shape->cylinder);
	if (!get_intersect_times(pers_ray, shape->cylinder, t))
		return ;
	tt = t[0];
	normal = get_cylinder_normal(ray, &shape->cylinder, tt);
	if (tt < 0 || intersects_vertically(pers_ray, tt, shape->cylinder.height)
		|| (ignore_normal != NULL && vec3_eq(*ignore_normal, normal)))
	{
		tt = t[1];
		normal = get_cylinder_normal(ray, &shape->cylinder, tt);
		if (intersects_vertically(pers_ray, tt, shape->cylinder.height)
			|| (ignore_normal != NULL && vec3_eq(*ignore_normal, normal)))
			return ;
	}
	if (tt >= best_hit->distance)
		return ;
	best_hit->distance = tt;
	best_hit->normal = normal;
	best_hit->shape = shape;
}
