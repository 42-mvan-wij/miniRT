/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/01 14:02:22 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/09/01 14:37:13 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "utils/utils.h"
#include "vec3/vec3.h"

void	intersect_plane(t_ray ray, t_rayhit *best_hit, t_object *shape)
{
	const long double	a = dot(ray.dir, shape->plane.norm);
	double				t;

	if (almost_equal(a, 0))
		return ;
	t = dot(shape->plane.norm, sub(shape->plane.coord, ray.origin)) / a;
	if (t < 0 || t >= best_hit->distance)
		return ;
	best_hit->distance = t;
	best_hit->normal = shape->plane.norm;
	best_hit->shape = shape;
}
