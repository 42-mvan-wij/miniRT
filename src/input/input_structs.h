/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_structs.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 14:42:21 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/08/22 18:12:54 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_STRUCTS_H
# define INPUT_STRUCTS_H

typedef struct s_scene {

}	t_scene;

typedef enum s_object_type {
	AMBIENT_LIGHT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
}	t_object_type;

#endif
