/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_structs.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 14:42:21 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/09/06 17:54:00 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_STRUCTS_H
# define INPUT_STRUCTS_H

# include "utils/error_structs.h"

typedef enum s_object_type {
	AMBIENT_LIGHT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
}	t_object_type;

typedef struct s_vec3 {
	long double	x;
	long double	y;
	long double	z;
}	t_vec3;

typedef struct s_ambient {
	long double	ratio;
	int			rgb;
}	t_ambient;

typedef struct s_camera {
	t_vec3		coord;
	t_vec3		norm;
	int			fov;
}	t_camera;

typedef struct s_light {
	t_vec3		coord;
	long double	brightness;
	int			rgb; // unused in mandatory part
}	t_light;

typedef struct s_sphere {
	t_vec3		coord;
	long double	radius; // convert from diameter
	int			rgb;
}	t_sphere;

typedef struct s_plane {
	t_vec3		coord;
	t_vec3		norm;
	int			rgb;
}	t_plane;

typedef struct s_cylinder {
	t_vec3		coord;
	t_vec3		norm;
	long double	radius; // converted from diameter and height
	int			rgb;
}	t_cylinder;

typedef struct s_object
{
	t_object_type	type;
	union
	{
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
	};
	t_object		*next;
}	t_object;

typedef struct s_scene {
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_object	*objects;
}	t_scene;

#endif
