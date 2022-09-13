/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_sphere.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 17:47:03 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/09/13 14:01:57 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "input/input.h"
#include "utils/utils.h"
#include <stdlib.h>

// TODO: testing
t_status	parse_sphere(char **line, t_scene *scene)
{
	t_object	obj;

	obj.type = SPHERE;
	if (parse_vec_field(line, &obj.sphere.coord) != OK)
		return (FAIL);
	if (parse_float_field(line, &obj.sphere.radius) != OK)
		return (FAIL);
	obj.sphere.radius /= 2;
	if (parse_rgb_field(line, &obj.sphere.rgb) != OK)
		return (FAIL);
	rt_lstnew_back(&scene->objects, obj);
	return (OK);
}
