/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_ambient_light.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/27 12:30:21 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/08/27 13:25:19 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "input/input.h"

#include <stdio.h>



// parse rgb
t_status	parse_ambient_light(t_scene *scene, char **line)
{
	int red;
	int green;
	int blue;

	if (parse_float_field_advance(line, &scene->ambient.ratio) != OK)
		return (FAIL);
	if (parse_int_field_advance(line, &red) != OK)
		return (FAIL);
	line++;
	if (parse_int_field_advance(line, &green) != OK)
		return (FAIL);
	line++;
	if (parse_int_field_advance(line, &blue) != OK)
		return (FAIL);
	scene->ambient.rgb = (red << 16 | green << 8 | blue);
	return (OK);
}
