/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_normal_field.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/27 15:05:33 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/09/19 11:44:02 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "input/input.h"
#include "utils/utils.h"
#include "vec3/vec3.h"
#include <stdlib.h>

t_status	parse_normal_field(char **line, t_vec3 *vec)
{
	if (parse_vec_field(line, vec) != OK)
		return (FAIL);
	if (!almost_equal(mag2(*vec), 1))
		return (rt_set_error(E_EXPECTED_NORMAL, NULL));
	return (OK);
}
