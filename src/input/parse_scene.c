/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_scene.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 14:12:14 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/09/10 15:53:55 by rvan-duy      ########   odam.nl         */
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
	};

	return (jump_table[type](line, scene));
}

t_status	parse_scene_line(char *line, t_scene *scene)
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

t_status	parse_scene(char *scene_path, t_scene *scene)
{
	int		fd;
	char	*line;
	int		gnl;

	fd = open(scene_path, O_RDONLY);
	if (fd < 0)
		return (rt_set_error(E_OPEN, scene_path));
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
	// printf("------------ SCENE ------------\n");
	// printf("Ambient: (%Lf, %d)\n", scene->ambient.ratio, scene->ambient.rgb);
	// printf("Camera:  ((%Lf, %Lf, %Lf), (%Lf, %Lf, %Lf), %d)\n", scene->camera.coord.x, scene->camera.coord.y, scene->camera.coord.z, scene->camera.norm.x, scene->camera.norm.y, scene->camera.norm.z, scene->camera.fov);
	// printf("Light:   ((%Lf, %Lf, %Lf), %Lf, %d)\n", scene->light.coord.x, scene->light.coord.y, scene->light.coord.z, scene->light.brightness, scene->light.rgb);
	// while (scene->objects) {
	// 	if (scene->objects->type == SPHERE)
	// 		printf("sphere:  ((%Lf, %Lf, %Lf), %Lf, %d)\n", scene->objects->sphere.coord.x, scene->objects->sphere.coord.y, scene->objects->sphere.coord.z, scene->objects->sphere.radius, scene->objects->sphere.rgb);
	// 	scene->objects = scene->objects->next;
	// }
	exit(200);
	return (OK);
}
