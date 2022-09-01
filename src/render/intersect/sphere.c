/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/01 14:02:39 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/09/01 14:40:15 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "structs.h"
#include "vec3/vec3.h"

bool	intersect_sphere_comp(t_ray ray, t_vec3 origin, long double radius, long double t[2])
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
void	intersect_sphere(t_ray ray, t_rayhit *best_hit, t_object *shape)
{
	long double	t[2];
	long double	tt;

	if (!intersect_sphere_comp(ray, shape->sphere.coord, shape->sphere.radius, t))
		return ;
	tt = t[0];
	if (tt < 0)
		tt = t[1];
	if (tt >= best_hit->distance)
		return ;
	best_hit->distance = tt;
	best_hit->normal = normalize(sub(add(ray.origin, scale(ray.dir, tt)), shape->sphere.coord));
	best_hit->shape = shape;
}
