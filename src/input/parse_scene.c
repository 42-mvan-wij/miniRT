/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_scene.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 14:12:14 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/09/13 16:47:46 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "utils/utils.h"
#include "libft.h"
#include "input/input.h"
#include "input/input_structs.h"
#include <stdlib.h>
#include <fcntl.h>

// printf("------------ SCENE ------------\n");
// printf("Ambient: (%Lf, %d)\n", scene->ambient.brightness, scene->ambient.rgba);
// printf("Camera:  ((%Lf, %Lf, %Lf), (%Lf, %Lf, %Lf), %d)\n", scene->camera.pos.x, scene->camera.pos.y, scene->camera.pos.z, scene->camera.norm.x, scene->camera.norm.y, scene->camera.norm.z, scene->camera.fov);
// printf("Light:   ((%Lf, %Lf, %Lf), %Lf, %d)\n", scene->light.pos.x, scene->light.pos.y, scene->light.pos.z, scene->light.brightness, scene->light.rgba);
// while (scene->objects) {
// 	if (scene->objects->type == SPHERE)
// 		printf("sphere:  ((%Lf, %Lf, %Lf), %Lf, %d)\n", scene->objects->sphere.pos.x, scene->objects->sphere.pos.y, scene->objects->sphere.pos.z, scene->objects->sphere.radius, scene->objects->sphere.rgba);
// 	else if (scene->objects->type == PLANE)
// 		printf("plane:   ((%Lf, %Lf, %Lf), (%Lf, %Lf, %Lf), %d)\n", scene->objects->plane.pos.x, scene->objects->plane.pos.y, scene->objects->plane.pos.z, scene->objects->plane.norm.x, scene->objects->plane.norm.y, scene->objects->plane.norm.z, scene->objects->plane.rgba);
// 	else if (scene->objects->type == CYLINDER)
// 		printf("cylinder:  ((%Lf, %Lf, %Lf), (%Lf, %Lf, %Lf), %Lf, %Lf, %d)\n", scene->objects->cylinder.pos.x, scene->objects->cylinder.pos.y, scene->objects->cylinder.pos.z, scene->objects->cylinder.norm.x, scene->objects->cylinder.norm.y, scene->objects->cylinder.norm.z, scene->objects->cylinder.radius, scene->objects->cylinder.height, scene->objects->cylinder.rgba);
// 	scene->objects = scene->objects->next;
// }

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

static t_status	parse_scene_line(char *line, t_scene *scene)
{
	t_object_type	type;

	while (ft_isspace(*line))
		line++;
	if (line[0] == '\0')
		return (OK);
	if (parse_type(&line, &type) != OK)
		return (FAIL);
	if (parse_element(type, &line, scene) != OK)
		return (FAIL);
	return (OK);
}

static t_status	open_file(char *scene_path, int *fd)
{
	if (ft_strncmp(scene_path + ft_strlen(scene_path) - 3, ".rt", 3) != OK)
		return (rt_set_error(E_EXPECTED_RT_FILE, NULL));
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
	close(fd);
	if (gnl < 0)
		return (rt_set_error(E_GNL, NULL));
	return (OK);
}
