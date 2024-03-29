/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_light.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/27 15:29:57 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/09/27 11:55:25 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "input/input.h"
#include "utils/utils.h"

t_status	parse_light(char **line, t_scene *scene)
{
	if (parse_vec_field(line, &scene->light.pos) != OK)
		return (FAIL);
	if (parse_float_field(line, &scene->light.brightness) != OK)
		return (FAIL);
	if (scene->light.brightness < 0 || scene->light.brightness > 1)
		return (rt_set_error(E_EXPECTED_FLOAT, " in range of [0.0 - 1.0]"));
	if (parse_rgb_field(line, &scene->light.rgba) != OK)
		return (FAIL);
	scene->light.is_present = true;
	return (OK);
}
