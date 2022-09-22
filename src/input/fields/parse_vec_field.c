/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_vec_field.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/27 15:05:33 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/09/22 16:58:18 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "input/input.h"
#include "utils/utils.h"
#include <stdlib.h>

t_status	parse_vec_advance(char **line, t_vec3 *vec)
{
	if (parse_float_advance(line, &vec->x) != OK)
		return (FAIL);
	if (**line != ',')
		return (rt_set_error(E_EXPECTED_VEC, NULL));
	(*line)++;
	if (parse_float_advance(line, &vec->y) != OK)
		return (FAIL);
	if (**line != ',')
		return (rt_set_error(E_EXPECTED_VEC, NULL));
	(*line)++;
	if (parse_float_advance(line, &vec->z) != OK)
		return (FAIL);
	return (OK);
}

t_status	parse_vec_field(char **line, t_vec3 *vec)
{
	if (parse_vec_advance(line, vec) != OK)
		return (FAIL);
	while (ft_isspace(**line))
		(*line)++;
	return (OK);
}
