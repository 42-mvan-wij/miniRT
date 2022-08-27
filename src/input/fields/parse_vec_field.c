/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_vec_field.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/27 15:05:33 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/08/27 15:09:10 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "input/input.h"
#include "utils/utils.h"
#include <stdlib.h>

t_status    parse_vec_field(char **line, t_vec3 *vec)
{
    if (parse_float_field(line, &vec->x) != OK)
        return (FAIL);
    (*line)++;
    if (parse_float_field(line, &vec->y) != OK)
        return (FAIL);
    (*line)++;
    if (parse_float_field(line, &vec->z) != OK)
        return (FAIL);
    return (OK);
}
