/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_structs.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 14:42:21 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/08/23 15:19:00 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_STRUCTS_H
# define INPUT_STRUCTS_H

# include "libft.h"
# include "structs.h"

typedef struct s_scene {
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_list		*objects;
}	t_scene;

#endif
