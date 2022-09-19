/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_plane.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/09 09:48:10 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/09/19 11:45:30 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "input/input.h"
#include "utils/utils.h"
#include <stdlib.h>

t_status	parse_plane(char **line, t_scene *scene)
{
	t_object	obj;

	obj.type = PLANE;
	if (parse_vec_field(line, &obj.plane.pos) != OK)
		return (FAIL);
	if (parse_normal_field(line, &obj.plane.norm) != OK)
		return (FAIL);
	if (parse_rgb_field(line, &obj.plane.rgba) != OK)
		return (FAIL);
	if (rt_lstnew_back(&scene->objects, obj) == NULL)
		return (rt_set_error(E_MALLOC, NULL));
	return (OK);
}
