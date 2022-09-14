/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   trace.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/01 14:29:31 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/09/14 10:14:41 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "structs.h"
#include "render/intersect/intersect.h"
#include "vec3/vec3.h"

void	init_rayhit(t_rayhit *rayhit)
{
	rayhit->distance = INFINITY;
	rayhit->normal = vec3(0, 0, 0);
}

void	intersect(t_ray ray, t_rayhit *best_hit, t_object *shape,
			t_vec3 *ignore_normal)
{
	if (shape->type == SPHERE)
		intersect_sphere(ray, best_hit, shape, ignore_normal);
	if (shape->type == PLANE)
		intersect_plane(ray, best_hit, shape, ignore_normal);
	if (shape->type == CYLINDER)
		intersect_cylinder(ray, best_hit, shape, ignore_normal);
}

t_vec3	get_vis_normal(t_ray ray, t_rayhit hit)
{
	if (dot(ray.dir, hit.normal) <= 0)
		return (hit.normal);
	return (scale(hit.normal, -1));
}

t_rayhit	trace(t_ray ray, t_shape_list *shapes, t_rayhit *ignore)
{
	t_rayhit	best_hit;

	init_rayhit(&best_hit);
	while (shapes != NULL)
	{
		if (ignore != NULL && &shapes->shape == ignore->shape)
			intersect(ray, &best_hit, &shapes->shape, &ignore->normal);
		else
			intersect(ray, &best_hit, &shapes->shape, NULL);
		shapes = shapes->next;
	}
	best_hit.vis_normal = get_vis_normal(ray, best_hit);
	return (best_hit);
}
