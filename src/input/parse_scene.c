/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_scene.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 14:12:14 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/08/27 13:57:53 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "utils/utils.h"
#include "libft.h"
#include "input/input.h"
#include "input/input_structs.h"
#include "input/elements/elements.h"
#include <stdlib.h>
#include <fcntl.h>

typedef t_status	(*t_parse_fn)(t_scene *, char **);

static t_status	parse_element(t_object_type type, t_scene *scene, char **line)
{
	static const t_parse_fn	jump_table[] = {
	[AMBIENT_LIGHT] = &parse_ambient_light,
	};

	return (jump_table[type](scene, line));
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
	if (parse_element(type, scene, &line) != OK)
		return (FAIL);
	return (OK);
}

// TEMP_COMMENT: parses the file line by line
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
	return (OK);
}
