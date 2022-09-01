/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/01 14:00:09 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/09/01 14:23:52 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "vec3/vec3.h"

t_color	vec2color(t_vec3 v)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	if (v.x > 1)
		r = 255;
	else if (v.x < 0)
		r = 0;
	else
		r = v.x * 255;
	if (v.y > 1)
		g = 255;
	else if (v.y < 0)
		g = 0;
	else
		g = v.y * 255;
	if (v.z > 1)
		b = 255;
	else if (v.z < 0)
		b = 0;
	else
		b = v.z * 255;
	a = 255;
	return (r << 24 | g << 16 | b << 8 | a << 0);
}

t_vec3	color2vec(t_color c)
{
	return (scale(vec3(
				(c >> 24) & 0xFF,
				(c >> 16) & 0xFF,
				(c >> 8) & 0xFF), 1.0 / 255.0));
}

t_vec3	scale_color(t_vec3 color1, t_vec3 color2)
{
	return (vec3(
			color1.x * color2.x,
			color1.y * color2.y,
			color1.z * color2.z));
}
