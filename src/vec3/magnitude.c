/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   magnitude.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/01 13:51:15 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/09/01 14:40:47 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "structs.h"
#include "vec3/vec3.h"

long double	mag2(t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

long double	mag(t_vec3 v)
{
	return (sqrtl(mag2(v)));
}

long double	dist2(t_vec3 v1, t_vec3 v2)
{
	return (mag2(sub(v1, v2)));
}

long double	dist(t_vec3 v1, t_vec3 v2)
{
	return (sqrtl(dist2(v1, v2)));
}

t_vec3	normalize(t_vec3 v)
{
	return (scale(v, 1 / mag(v)));
}
