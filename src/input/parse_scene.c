/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_scene.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 14:12:14 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/09/27 13:05:55 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "utils/utils.h"
#include "libft.h"
#include "input/input.h"
#include "input/input_structs.h"
#include <stdlib.h>
#include <fcntl.h>

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

static t_status	parse_scene_line(char *line, t_scene *scene)
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

static t_status	open_file(char *scene_path, int *fd)
{
	*fd = open(scene_path, O_RDONLY);
	if (*fd < 0)
		return (rt_set_error(E_OPEN, scene_path));
	return (OK);
}

t_status	parse_scene(char *scene_path, t_scene *scene)
{
	int		fd;
	char	*line;
	int		gnl;

	scene->objects = NULL;
	scene->ambient.is_present = false;
	scene->camera.is_present = false;
	scene->light.is_present = false;
	if (open_file(scene_path, &fd) != OK)
		return (FAIL);
	gnl = get_next_line(fd, &line);
	while (gnl != -1)
	{
		if (parse_scene_line(line, scene) != OK)
		{
			free(line);
			close(fd);
			return (FAIL);
		}
		free(line);
		if (gnl == 0)
			break ;
		gnl = get_next_line(fd, &line);
	}
	if (scene->ambient.is_present == false)
		return (rt_set_error(E_MISSING_REQUIRED_ELEMENT, "ambient light"));
	if (scene->camera.is_present == false)
		return (rt_set_error(E_MISSING_REQUIRED_ELEMENT, "camera"));
	if (scene->light.is_present == false)
		return (rt_set_error(E_MISSING_REQUIRED_ELEMENT, "light"));
	close(fd);
	if (gnl < 0)
		return (rt_set_error(E_GNL, NULL));
	return (OK);
}
