/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   angle.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/20 17:07:03 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/09/20 17:08:15 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "vec3/vec3.h"
#include "utils/utils.h"
#include <math.h>

void	cos_sin(t_vec3 v1, t_vec3 v2, long double cos_and_sin[2])
{
	t_vec3		c;

	cos_and_sin[COS] = dot(v1, v2) / sqrtl(mag2(v1) * mag2(v2));
	cos_and_sin[SIN] = sin_from_cos(cos_and_sin[COS]);
	c = cross(v1, v2);
	if (c.y >= 0)
		cos_and_sin[SIN] *= -1;
}
