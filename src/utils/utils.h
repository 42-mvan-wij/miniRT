/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 16:31:15 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/09/13 14:04:56 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "structs.h"

t_error_data	rt_get_error_data(void);
t_status		rt_set_error(t_error error, char *error_data_text);
t_shape_list	*rt_lstnew_back(t_shape_list **head, t_object new);
long double		sin_from_cos(long double cos_a);
bool			almost_equal(long double a, long double b);
t_color			vec2color(t_vec3 v);
t_vec3			color2vec(t_color c);
t_vec3			scale_color(t_vec3 color1, t_vec3 color2);

#endif
