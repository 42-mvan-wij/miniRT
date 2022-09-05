/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/01 14:01:40 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/09/05 12:40:39 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "utils/utils.h"
#include "vec3/vec3.h"
#include "render/intersect/intersect.h"

t_vec3	get_cylinder_normal(t_ray ray, t_cylinder *cylinder, long double t)
{
	t_vec3	point;
	t_vec3	dir;

	point = add(scale(ray.dir, t), ray.origin);
	dir = sub(point, cylinder->coord);
	return (normalize(cross(cross(cylinder->norm, dir), cylinder->norm)));
}

t_ray	in_cylinder_perspective(t_ray ray, t_cylinder *cylinder)
{
	t_vec3		flat_normal;
	long double	cos_sin_a[2];
	long double	cos_sin_b[2];
	t_matrix	m;
	t_ray		out_ray;

	if (almost_equal(cylinder->norm.y, 1))
		m = matrix_from_vecs(vec3(1, 0, 0), vec3(0, 1, 0), vec3(0, 0, 1));
	else
	{
		flat_normal = cylinder->norm;
		flat_normal.y = 0;
		cos_sin_a[COS] = dot(vec3(1, 0, 0), flat_normal) / mag(flat_normal);
		cos_sin_a[SIN] = sin_from_cos(cos_sin_a[COS]);
		cos_sin_b[COS] = dot(vec3(0, 1, 0), cylinder->norm);
		cos_sin_b[SIN] = sin_from_cos(cos_sin_b[COS]);
		m = compose(
				matrix_from_vecs(vec3(cos_sin_a[COS], 0, -cos_sin_a[SIN]),
					vec3(0, 1, 0), vec3(cos_sin_a[SIN], 0, cos_sin_a[COS])),
				matrix_from_vecs(vec3(-cos_sin_b[SIN], cos_sin_b[COS], 0),
					vec3(cos_sin_b[COS], cos_sin_b[SIN], 0), vec3(0, 0, 1)));
	}
	out_ray.rgb_energy = ray.rgb_energy; // not really needed
	out_ray.dir = transform(ray.dir, m);
	out_ray.origin = transform(sub(ray.origin, cylinder->coord), m);
	return (out_ray);
}

void	intersect_cylinder(t_ray ray, t_rayhit *best_hit, t_object *shape, t_vec3 *ignore_normal)
{
	t_ray		pers_ray;
	t_ray		flat_ray;
	long double	t[2];
	long double	tt;
	t_vec3		normal;

	pers_ray = in_cylinder_perspective(ray, &shape->cylinder);
	flat_ray.origin = vec3(pers_ray.origin.x, 0, pers_ray.origin.z);
	flat_ray.dir = normalize(vec3(pers_ray.dir.x, 0, pers_ray.dir.z));
	flat_ray.rgb_energy = ray.rgb_energy; // not really needed
	if (!intersect_sphere_comp(flat_ray, vec3(0, 0, 0), shape->cylinder.radius, t))
		return ;
	tt = t[0] / dot(pers_ray.dir, flat_ray.dir);
	normal = get_cylinder_normal(ray, &shape->cylinder, tt);
	if (tt < 0 || pers_ray.dir.y * tt + pers_ray.origin.y < -shape->cylinder.height / 2 || pers_ray.dir.y * tt + pers_ray.origin.y > shape->cylinder.height / 2 || (ignore_normal != NULL && vec3_eq(*ignore_normal, normal)))
	{
		tt = t[1] / dot(pers_ray.dir, flat_ray.dir);
		normal = get_cylinder_normal(ray, &shape->cylinder, tt);
		if (pers_ray.dir.y * tt + pers_ray.origin.y < -shape->cylinder.height / 2 || pers_ray.dir.y * tt + pers_ray.origin.y > shape->cylinder.height / 2 || (ignore_normal != NULL && vec3_eq(*ignore_normal, normal)))
			return ;
	}
	if (tt >= best_hit->distance)
		return ;
	best_hit->distance = tt;
	best_hit->normal = normal;
	best_hit->shape = shape;
}
