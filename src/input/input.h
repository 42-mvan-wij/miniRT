/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 14:47:26 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/08/27 13:44:54 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "structs.h"

t_status	parse_scene(char *scene_path, t_scene *scene);
t_status	parse_scene_line(char *line, t_scene *scene);
t_status	parse_type_advance(char **line, t_object_type *type);
t_status	parse_int_field_advance(char **line, int *i);
t_status	parse_float_field_advance(char **line, long double *f);
t_status    parse_rgb_field(char **line, int *rgb);

#endif
