/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_camera.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/27 15:03:53 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/09/27 11:55:20 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "input/input.h"
#include "utils/utils.h"
#include <stdlib.h>

t_status	parse_camera(char **line, t_scene *scene)
{
	if (parse_vec_field(line, &scene->camera.pos) != OK)
		return (FAIL);
	if (parse_normal_field(line, &scene->camera.norm) != OK)
		return (FAIL);
	if (parse_int_field(line, &scene->camera.fov) != OK)
		return (FAIL);
	if (scene->camera.fov < 0 || scene->camera.fov > 180)
		return (rt_set_error(E_EXPECTED_INTEGER, " in range of [0 - 180]"));
	scene->camera.is_present = true;
	return (OK);
}
