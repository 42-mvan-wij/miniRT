/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_type.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 15:31:21 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/08/23 15:50:09 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "input/input_structs.h"
#include "utils/utils.h"
#include "libft.h"
#include <stdlib.h>

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
		return (rt_set_error(E_EXPECTED_IDENTIFIER, NULL)); // argument is NULL, correct? prob not
	return (OK);
}

t_status	parse_type(char **line, t_object_type *type)
{
	if (get_type(*line, type) != OK)
		return (FAIL);
	while (ft_isalpha(**line))
		(*line)++;
	while (ft_isspace(**line))
		(*line)++;
	return (OK);
}
