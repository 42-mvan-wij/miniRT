/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 14:47:26 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/08/23 15:50:31 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "structs.h"

t_status	parse_scene(char *scene_path, t_scene *scene);
t_status	parse_scene_line(char *line, t_scene *scene);
t_status	parse_type_advance(char **line, t_object_type *type);
t_status	parse_int_advance(char **line, int *i);
t_status	parse_float_advance(char **line, long double *f);

#endif
