/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   multiply.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/01 13:58:02 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/09/01 14:19:24 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "vec3/vec3.h"

// project v1 onto v2 and multiply length by length of v2, order doesn't matter
long double	dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x
		+ v1.y * v2.y
		+ v1.z * v2.z);
}

t_vec3	cross(t_vec3 v1, t_vec3 v2)
{
	return (vec3(
			v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x));
}
