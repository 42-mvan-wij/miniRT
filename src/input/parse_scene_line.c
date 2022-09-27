/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_scene_line.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/27 14:00:32 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/09/27 14:13:44 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "input/input.h"
#include "utils/utils.h"

typedef t_status	(*t_parse_fn)(char **, t_scene *);

static t_status	parse_element(t_object_type type, char **line, t_scene *scene)
{
	static const t_parse_fn	jump_table[] = {
	[AMBIENT_LIGHT] = &parse_ambient_light,
	[CAMERA] = &parse_camera,
	[LIGHT] = &parse_light,
	[SPHERE] = &parse_sphere,
	[PLANE] = &parse_plane,
	[CYLINDER] = &parse_cylinder,
	};

	return (jump_table[type](line, scene));
}

static bool	unique_element_already_exists(t_object_type type, t_scene *scene)
{
	if (type == CAMERA && scene->camera.is_present)
		return (true);
	if (type == AMBIENT_LIGHT && scene->ambient.is_present)
		return (true);
	if (type == LIGHT && scene->light.is_present)
		return (true);
	return (false);
}

static char	*get_type_str(t_object_type type)
{
	static const char	*lookup_table[] = {
	[AMBIENT_LIGHT] = "ambient light",
	[CAMERA] = "camera",
	[LIGHT] = "light",
	[SPHERE] = "sphere",
	[PLANE] = "plane",
	[CYLINDER] = "cylinder",
	};

	return ((char *)lookup_table[type]);
}

t_status	parse_scene_line(char *line, t_scene *scene)
{
	t_object_type	type;

	while (ft_isspace(*line))
		line++;
	if (line[0] == '\0' || line[0] == '#')
		return (OK);
	if (parse_type(&line, &type) != OK)
		return (FAIL);
	if (unique_element_already_exists(type, scene))
		return (rt_set_error(E_DUPLICATE_UNIQUE_ELEMENT, get_type_str(type)));
	if (parse_element(type, &line, scene) != OK)
		return (FAIL);
	if (*line != '\0')
		return (rt_set_error(E_EXTRA_TEXT, line));
	return (OK);
}
