/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_ambient_light.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/27 12:30:21 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/08/27 14:12:43 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "input/input.h"
#include "utils/utils.h"
#include <stdlib.h>

t_status	parse_ambient_light(char **line, t_scene *scene)
{
	if (parse_float_field(line, &scene->ambient.ratio) != OK)
		return (FAIL);
	if (scene->ambient.ratio < 0.0 || scene->ambient.ratio > 1.0)
		return (rt_set_error(E_EXPECTED_FLOAT, " in range [0.0 - 1.0]"));
	if (parse_rgb_field(line, &scene->ambient.rgb) != OK)
		return (FAIL);
	return (OK);
}
