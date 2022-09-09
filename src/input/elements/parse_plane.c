/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_plane.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/09 09:48:10 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/09/09 09:54:13 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "input/input.h"
#include "utils/utils.h"

// TODO: testing
void	parse_plane(char **line, t_scene *scene)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (obj == NULL)
		return (FAIL);
	obj->type = PLANE;
	if (parse_vec_field(line, &obj->plane.coord) != OK)
		return (FAIL);
	if (parse_vec_field(line, &obj->plane.norm) != OK)
		return (FAIL);
	if (obj->plane.norm.x < -1 || obj->plane.norm.x > 1 || \
		obj->plane.norm.y < -1 || obj->plane.norm.y > 1 || \
		obj->plane.norm.z < -1 || obj->plane.norm.z > 1)
		return (rt_set_error(E_EXPECTED_FLOAT, " in range of [-1.0 - 1.0]"));
	if (parse_rgb_field(line, &obj->plane.rgb) != OK)
		return (FAIL);
	rt_lstadd_back(&scene->objects, obj);
}
