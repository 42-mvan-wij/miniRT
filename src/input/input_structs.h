/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_structs.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 14:42:21 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/09/27 11:49:02 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_STRUCTS_H
# define INPUT_STRUCTS_H

# include <MLX42.h>
# include "libft.h"
# include "vec3/vec3_structs.h"

typedef struct s_ambient {
	long double	brightness;
	uint32_t	rgba;
	bool		is_present;
}	t_ambient;

typedef struct s_camera {
	t_vec3		pos;
	t_vec3		norm;
	int			fov;
	bool		is_present;
}	t_camera;

typedef struct s_light {
	t_vec3		pos;
	long double	brightness;
	uint32_t	rgba;
	bool		is_present;
}	t_light;

typedef struct s_sphere {
	t_vec3		pos;
	long double	radius;
	uint32_t	rgba;
}	t_sphere;

typedef struct s_plane {
	t_vec3		pos;
	t_vec3		norm;
	uint32_t	rgba;
}	t_plane;

typedef struct s_cylinder {
	t_vec3		pos;
	t_vec3		norm;
	long double	radius;
	long double	height;
	uint32_t	rgba;
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
	union
	{
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
	};
}	t_object;

typedef struct s_shape_list {
	struct s_shape_list	*next;
	t_object			shape;
}	t_shape_list;

typedef struct s_scene {
	t_ambient			ambient;
	t_camera			camera;
	t_light				light;
	struct s_shape_list	*objects;
}	t_scene;

////////////////////////////////////////////////////////////////////////////////

typedef struct s_rt_data {
	int			height;
	int			width;
	t_scene		scene;
	mlx_t		*mlx;
	mlx_image_t	*image;
	bool		render_next;
}	t_rt_data;

#endif
