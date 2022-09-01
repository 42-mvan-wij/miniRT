/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotate.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/01 13:57:33 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/09/01 14:40:55 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "structs.h"
#include "vec3/vec3.h"

t_vec3	rot(t_vec3 v, t_vec3 axis, long double angle)
{
	const long double	cos_a = cosl(angle);

	return (add(add(
				scale(axis, (1 - cos_a) * dot(v, axis)),
				scale(v, cos_a)),
			scale(cross(axis, v), sinl(angle))));
}
