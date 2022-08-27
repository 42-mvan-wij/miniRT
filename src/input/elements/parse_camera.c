/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_camera.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/27 15:03:53 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/08/27 15:33:32 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "input/input.h"
#include "utils/utils.h"
#include <stdlib.h>

t_status    parse_camera(char **line, t_scene *scene)
{
    if (parse_vec_field(line, &scene->camera.coord) != OK)
        return (FAIL);
    if (parse_vec_field(line, &scene->camera.norm) != OK)
        return (FAIL);
    if (scene->camera.norm.x < -1 || scene->camera.norm.x > 1 || \
        scene->camera.norm.y < -1 || scene->camera.norm.y > 1 || \
        scene->camera.norm.z < -1 || scene->camera.norm.z > 1)
        return (rt_set_error(E_EXPECTED_FLOAT, " in range of [-1.0 - 1.0]"));
    if (parse_int_field(line, &scene->camera.fov) != OK)
        return (FAIL);
    if (scene->camera.fov < 0 || scene->camera.fov > 180)
        return (rt_set_error(E_EXPECTED_INTEGER, " in range of [0 - 180]"));
    return (OK);
}
