/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   trace.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/01 14:29:31 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/09/01 14:41:45 by mvan-wij      ########   odam.nl         */
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

void	intersect(t_ray ray, t_rayhit *best_hit, t_object *shape)
{
	if (shape->type == SPHERE)
		intersect_sphere(ray, best_hit, shape);
	if (shape->type == PLANE)
		intersect_plane(ray, best_hit, shape);
	if (shape->type == CYLINDER)
		intersect_cylinder(ray, best_hit, shape);
}

t_rayhit	trace(t_ray ray, t_shape_list *shapes, t_rayhit *ignore)
{
	t_rayhit	old_hit;
	t_rayhit	best_hit;

	init_rayhit(&best_hit);
	while (shapes != NULL)
	{
		if (ignore != NULL && &shapes->shape == ignore->shape)
		{
			old_hit = best_hit;
			intersect(ray, &best_hit, &shapes->shape);
			if (best_hit.shape == ignore->shape && vec3_eq(best_hit.normal, ignore->normal))
				best_hit = old_hit;
		}
		else
			intersect(ray, &best_hit, &shapes->shape);
		shapes = shapes->next;
	}
	return (best_hit);
}
