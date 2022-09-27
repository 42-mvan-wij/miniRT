/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_scene.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 14:12:14 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/09/27 14:15:50 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "utils/utils.h"
#include "input/input.h"
#include <stdlib.h>
#include <fcntl.h>

static void	init_scene_vars(t_scene *scene)
{
	scene->objects = NULL;
	scene->camera.is_present = false;
	scene->ambient.is_present = false;
	scene->light.is_present = false;
}

static t_status	open_file(char *scene_path, int *fd)
{
	*fd = open(scene_path, O_RDONLY);
	if (*fd < 0)
		return (rt_set_error(E_OPEN, scene_path));
	return (OK);
}

static t_status	check_required_elements(t_scene *scene)
{
	if (scene->camera.is_present == false)
		return (rt_set_error(E_MISSING_REQUIRED_ELEMENT, "camera"));
	if (scene->ambient.is_present == false)
		return (rt_set_error(E_MISSING_REQUIRED_ELEMENT, "ambient light"));
	if (scene->light.is_present == false)
		return (rt_set_error(E_MISSING_REQUIRED_ELEMENT, "light"));
	return (OK);
}

static int	read_file(int fd, t_scene *scene)
{
	char	*line;
	int		gnl;

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
	return (gnl);
}

t_status	parse_scene(char *scene_path, t_scene *scene)
{
	int		fd;
	int		gnl;

	init_scene_vars(scene);
	if (open_file(scene_path, &fd) != OK)
		return (FAIL);
	gnl = read_file(fd, scene);
	close(fd);
	if (check_required_elements(scene))
		return (FAIL);
	if (gnl < 0)
		return (rt_set_error(E_GNL, NULL));
	return (OK);
}
