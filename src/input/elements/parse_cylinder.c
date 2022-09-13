/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_cylinder.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 12:05:14 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/09/13 13:59:54 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "input/input.h"
#include "utils/utils.h"
#include <stdlib.h>

// TODO: testing
t_status	parse_cylinder(char **line, t_scene *scene)
{
	t_object	obj;

	obj.type = CYLINDER;
	if (parse_vec_field(line, &obj.cylinder.coord) != OK)
		return (FAIL);
	if (parse_vec_field(line, &obj.cylinder.norm) != OK)
		return (FAIL);
	if (parse_float_field(line, &obj.cylinder.radius) != OK)
		return (FAIL);
	obj.cylinder.radius /= 2;
	if (parse_float_field(line, &obj.cylinder.height) != OK)
		return (FAIL);
	if (parse_rgb_field(line, &obj.cylinder.rgb) != OK)
		return (FAIL);
	rt_lstnew_back(&scene->objects, obj);
	return (OK);
}
