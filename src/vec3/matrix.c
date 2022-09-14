/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   matrix.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/01 13:55:38 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/09/14 10:09:14 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "vec3/vec3.h"

t_matrix	matrix_from_vecs(t_vec3 right, t_vec3 up, t_vec3 in)
{
	const t_matrix	matrix = {
		.data = {
		right.x, up.x, in.x,
		right.y, up.y, in.y,
		right.z, up.z, in.z,
	}};

	return (matrix);
}

t_matrix	matrix_dot(t_matrix m1, t_matrix m2)
{
	int			y;
	int			x;
	t_matrix	matrix;

	y = 0;
	while (y < 3)
	{
		x = 0;
		while (x < 3)
		{
			matrix.data[y * 3 + x]
				= m1.data[0 + y * 3] * m2.data[x + 0 * 3]
				+ m1.data[1 + y * 3] * m2.data[x + 1 * 3]
				+ m1.data[2 + y * 3] * m2.data[x + 2 * 3];
			x++;
		}
		y++;
	}
	return (matrix);
}

t_matrix	compose(t_matrix m1, t_matrix m2)
{
	return (matrix_dot(m2, m1));
}

t_vec3	transform(t_vec3 v, t_matrix m)
{
	return (vec3(
			v.x * m.data[0 + 0 * 3] + v.y * m.data[0 + 1 * 3]
			+ v.z * m.data[0 + 2 * 3],
			v.x * m.data[1 + 0 * 3] + v.y * m.data[1 + 1 * 3]
			+ v.z * m.data[1 + 2 * 3],
			v.x * m.data[2 + 0 * 3] + v.y * m.data[2 + 1 * 3]
			+ v.z * m.data[2 + 2 * 3]));
}
