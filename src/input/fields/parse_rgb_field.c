/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_rgb_field.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/27 13:28:26 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/09/06 17:37:34 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "input/input.h"
#include "utils/utils.h"
#include <stdlib.h>

t_status	parse_rgb_field(char **line, int *rgb)
{
	int	red;
	int	green;
	int	blue;

	if (parse_int_field(line, &red) != OK)
		return (FAIL);
	(*line)++;
	if (parse_int_field(line, &green) != OK)
		return (FAIL);
	(*line)++;
	if (parse_int_field(line, &blue) != OK)
		return (FAIL);
	if (red < 0 || red > 255 || \
		green < 0 || green > 255 || \
		blue < 0 || blue > 255)
		return (rt_set_error(E_EXPECTED_INTEGER, " in range [0 - 255]"));
	*rgb = (red << 16 | green << 8 | blue);
	return (OK);
}
