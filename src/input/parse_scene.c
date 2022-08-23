/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_scene.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 14:12:14 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/08/23 15:19:16 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "utils/utils.h"
#include "libft.h"
#include <stdlib.h>
#include <fcntl.h>

static void	rt_atodl_strict_skipper(char *str, size_t *skip, size_t *non_digits)
{
	while (ft_isspace(str[*skip]))
	{
		(*non_digits)++;
		(*skip)++;
	}
	if (str[*skip] == '+' || str[*skip] == '-')
	{
		(*non_digits)++;
		(*skip)++;
	}
	while (ft_isdigit(str[*skip]))
		(*skip)++;
	if (str[*skip] == '.')
	{
		(*skip)++;
		(*non_digits)++;
	}
	while (ft_isdigit(str[*skip]))
		(*skip)++;
}

static t_status	parse_float_advance(char **line, long double *f)
{
	size_t	skipped;
	size_t	non_digits;

	*f = 0;
	skipped = 0;
	non_digits = 0;
	rt_atodl_strict_skipper(*line, &skipped, &non_digits);
	if (skipped == non_digits || (!ft_isspace((*line)[skipped]) \
	&& (*line)[skipped] != '\0'))
		return (rt_set_error(E_EXPECTED_FLOAT, NULL));
	*f = ft_atodl(*line);
	*line = &(*line)[skipped];
	return (OK);
}

t_status	parse_float_field_advance(char **line, long double *f)
{
	if (parse_float_advance(line, f) != OK)
		return (FAIL);
	while (ft_isspace(**line))
		(*line)++;
	return (OK);
}

static void	rt_atoi_strict_skipper(char *str, size_t *skip, size_t *non_digits)
{
	while (ft_isspace(str[*skip]))
	{
		(*non_digits)++;
		(*skip)++;
	}
	if (str[*skip] == '+' || str[*skip] == '-')
	{
		(*non_digits)++;
		(*skip)++;
	}
	while (ft_isdigit(str[*skip]))
		(*skip)++;
}

static t_status	parse_int_advance(char **line, int *i)
{
	size_t	skipped;
	size_t	non_digits;
	bool	had_overflow;

	*i = 0;
	skipped = 0;
	non_digits = 0;
	rt_atoi_strict_skipper(*line, &skipped, &non_digits);
	if (skipped == non_digits || (!ft_isspace((*line)[skipped]) \
	&& (*line)[skipped] != '\0'))
		return (rt_set_error(E_EXPECTED_INTEGER, NULL));
	*i = ft_atoi(*line, &had_overflow);
	if (had_overflow)
		return (rt_set_error(E_EXPECTED_INTEGER, NULL));
	*line = &(*line)[skipped];
	return (OK);
}

t_status	parse_int_field_advance(char **line, int *i)
{
	if (parse_int_advance(line, i) != OK)
		return (FAIL);
	while (ft_isspace(**line))
		(*line)++;
	return (OK);
}

static bool	is_type(char *line, char *id)
{
	size_t	len;

	len = ft_strlen(id);
	if (ft_strncmp(line, id, len) != 0)
		return (false);
	return (ft_isspace(line[len]) || line[len] == '\0');
}

static t_status	get_type(char *line, t_object_type *type)
{
	if (is_type(line, "A"))
		*type = AMBIENT_LIGHT;
	else if (is_type(line, "C"))
		*type = CAMERA;
	else if (is_type(line, "L"))
		*type = LIGHT;
	else if (is_type(line, "sp"))
		*type = SPHERE;
	else if (is_type(line, "pl"))
		*type = PLANE;
	else if (is_type(line, "cy"))
		*type = CYLINDER;
	else
		return (rt_set_error(E_EXPECTED_IDENTIFIER));
	return (OK);
}

static t_status	parse_type_advance(char **line, t_object_type *type)
{
	if (get_type(*line, type) != OK)
		return (FAIL);
	while (ft_isalpha(**line))
		(*line)++;
	while (ft_isspace(**line))
		(*line)++;
	return (OK);
}

static t_status	parse_scene_line(char *line, t_scene *scene)
{
	t_object_type	type;
	(void)scene;
	while (ft_isspace(*line))
		line++;
	if (line[0] == '\0')
		return (OK);
	if (parse_type_advance(&line, &type) != OK)
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
	return (OK);
}
