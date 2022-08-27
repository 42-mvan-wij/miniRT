/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_rgb_field.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/27 13:28:26 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/08/27 13:56:54 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "input/input_structs.h"
#include "utils/utils.h"
#include "input/input.h"
#include <stdlib.h>

t_status    parse_rgb_field(char **line, int *rgb)
{
    int red;
	int green;
	int blue;

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
        return (rt_set_error(E_EXPECTED_RGB_VALUE, NULL));
	*rgb = (red << 16 | green << 8 | blue);
    return (OK);
}