/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_sphere.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 17:47:03 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/09/13 17:11:33 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "input/input.h"
#include "utils/utils.h"
#include <stdlib.h>

t_status	parse_sphere(char **line, t_scene *scene)
{
	t_object	obj;

	obj.type = SPHERE;
	if (parse_vec_field(line, &obj.sphere.pos) != OK)
		return (FAIL);
	if (parse_float_field(line, &obj.sphere.radius) != OK)
		return (FAIL);
	obj.sphere.radius /= 2;
	if (parse_rgb_field(line, &obj.sphere.rgba) != OK)
		return (FAIL);
	if (rt_lstnew_back(&scene->objects, obj) == NULL)
		return (rt_set_error(E_MALLOC, NULL));
	return (OK);
}
