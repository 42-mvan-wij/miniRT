/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_structs.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 15:06:29 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/08/23 15:37:55 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_STRUCTS_H
# define RENDER_STRUCTS_H

# include "MLX42.h"

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
	long double	radius; // convert from diameter
	long double	height;
	int			rgb;
}	t_cylinder;

typedef enum s_object_type {
	AMBIENT_LIGHT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
}	t_object_type;

typedef struct s_object
{
	t_object_type	type;
	union {
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
	};
}	t_object;

////////////////////////////////////////////////////////////////////////////////

typedef struct s_rt_data {
	int				height;
	int				width;
	struct s_scene	*scene;
	mlx_t			*mlx;
	mlx_image_t		*image;
}	t_rt_data;

#endif
