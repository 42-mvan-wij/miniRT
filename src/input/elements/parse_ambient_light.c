/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_ambient_light.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/27 12:30:21 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/08/27 14:06:57 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "input/input.h"

t_status	parse_ambient_light(char **line, t_scene *scene)
{
	if (parse_float_field(line, &scene->ambient.ratio) != OK)
		return (FAIL);
	if (parse_rgb_field(line, &scene->ambient.rgb) != OK)
		return (FAIL);
	return (OK);
}
