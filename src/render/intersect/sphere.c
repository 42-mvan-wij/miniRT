/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/01 14:02:39 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/09/14 10:31:22 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "structs.h"
#include "vec3/vec3.h"

bool	intersect_sphere_comp(t_ray ray, t_vec3 origin, long double radius,
			long double t[2])
{
	const t_vec3		diff = sub(origin, ray.origin); // d
	const long double	tc = dot(diff, ray.dir); // p1
	long double			d2;
	long double			t1c; // p2

	d2 = mag2(diff) - tc * tc;
	if (d2 > radius * radius)
		return (false);
	t1c = sqrtl(radius * radius - d2);
	t[0] = tc - t1c;
	t[1] = tc + t1c;
	if (t[1] < 0)
		return (false);
	return (true);
}

// https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
// http://kylehalladay.com/blog/tutorial/math/2013/12/24/Ray-Sphere-Intersection.html
void	intersect_sphere(t_ray ray, t_rayhit *best_hit, t_object *shape,
			t_vec3 *ignore_normal)
{
	long double	t[2];
	long double	tt;
	t_vec3		normal;

	if (!intersect_sphere_comp(ray, shape->sphere.pos, shape->sphere.radius, t))
		return ;
	tt = t[0];
	normal = normalize(
			sub(add(ray.origin, scale(ray.dir, tt)), shape->sphere.pos));
	if (tt < 0 || (ignore_normal != NULL && vec3_eq(normal, *ignore_normal)))
	{
		tt = t[1];
		normal = normalize(
				sub(add(ray.origin, scale(ray.dir, tt)), shape->sphere.pos));
	}
	if (tt >= best_hit->distance
		|| (ignore_normal != NULL && vec3_eq(normal, *ignore_normal)))
		return ;
	best_hit->distance = tt;
	best_hit->normal = normal;
	best_hit->shape = shape;
}
