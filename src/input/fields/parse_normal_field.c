/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_normal_field.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/27 15:05:33 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/09/19 12:34:56 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "input/input.h"
#include "utils/utils.h"
#include "vec3/vec3.h"
#include <stdlib.h>
#include <math.h>

t_status	parse_normal_field(char **line, t_vec3 *vec)
{
	if (parse_vec_field(line, vec) != OK)
		return (FAIL);
	if (fabsl(mag2(*vec) - 1) > 0.001)
		return (rt_set_error(E_EXPECTED_NORMAL, NULL));
	*vec = normalize(*vec);
	return (OK);
}
