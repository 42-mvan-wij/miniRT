/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 15:11:57 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/08/24 14:36:28 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "structs.h"

void	render_frame(t_rt_data *rt_data);
t_vec3	vec3(long double x, long double y, long double z);

#endif
