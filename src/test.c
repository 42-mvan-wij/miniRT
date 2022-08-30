/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 15:32:30 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/08/30 15:51:51 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "libft.h"
#include "structs.h"
#include "input/input.h"
#include "utils/utils.h"
#include "render/render.h"
#include <stdlib.h>
#include <math.h>

void	loop_hook(void *param)
{
	t_rt_data	*rt_data;

	rt_data = param;
	if (mlx_is_key_down(rt_data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(rt_data->mlx);
	if (mlx_is_key_down(rt_data->mlx, MLX_KEY_SPACE))
		rt_data->scene.camera.coord.y += 0.1;
	if (mlx_is_key_down(rt_data->mlx, MLX_KEY_LEFT_SHIFT) || mlx_is_key_down(rt_data->mlx, MLX_KEY_RIGHT_SHIFT))
		rt_data->scene.camera.coord.y -= 0.1;
	if (mlx_is_key_down(rt_data->mlx, MLX_KEY_W))
	{
		t_vec3	forward = cross(cross(vec3(0, 1, 0), normalize(rt_data->scene.camera.norm)), vec3(0, 1, 0));
		rt_data->scene.camera.coord = add(rt_data->scene.camera.coord, scale(forward, 0.1));
	}
	if (mlx_is_key_down(rt_data->mlx, MLX_KEY_S))
	{
		t_vec3	forward = cross(cross(vec3(0, 1, 0), normalize(rt_data->scene.camera.norm)), vec3(0, 1, 0));
		rt_data->scene.camera.coord = add(rt_data->scene.camera.coord, scale(forward, -0.1));
	}
	if (mlx_is_key_down(rt_data->mlx, MLX_KEY_D))
	{
		t_vec3	right = cross(vec3(0, 1, 0), normalize(rt_data->scene.camera.norm));
		rt_data->scene.camera.coord = add(rt_data->scene.camera.coord, scale(right, 0.1));
	}
	if (mlx_is_key_down(rt_data->mlx, MLX_KEY_A))
	{
		t_vec3	right = cross(vec3(0, 1, 0), normalize(rt_data->scene.camera.norm));
		rt_data->scene.camera.coord = add(rt_data->scene.camera.coord, scale(right, -0.1));
	}
	if (mlx_is_key_down(rt_data->mlx, MLX_KEY_UP))
	{
		rt_data->scene.camera.norm = normalize(rot(rt_data->scene.camera.norm, cross(vec3(0, 1, 0), rt_data->scene.camera.norm), -0.1));
		// rt_data->scene.camera.norm
	}
	if (mlx_is_key_down(rt_data->mlx, MLX_KEY_DOWN))
	{
		rt_data->scene.camera.norm = normalize(rot(rt_data->scene.camera.norm, cross(vec3(0, 1, 0), rt_data->scene.camera.norm), 0.1));
		// rt_data->scene.camera.norm
	}
	if (mlx_is_key_down(rt_data->mlx, MLX_KEY_LEFT))
	{
		t_matrix m = matrix_from_vecs(vec3(cosl(-0.1), 0, sinl(-0.1)), vec3(0, 1, 0), vec3(-sinl(-0.1), 0, cosl(-0.1)));
		rt_data->scene.camera.norm = normalize(transform(rt_data->scene.camera.norm, m));
	}
	if (mlx_is_key_down(rt_data->mlx, MLX_KEY_RIGHT))
	{
		t_matrix m = matrix_from_vecs(vec3(cosl(0.1), 0, sinl(0.1)), vec3(0, 1, 0), vec3(-sinl(0.1), 0, cosl(0.1)));
		rt_data->scene.camera.norm = normalize(transform(rt_data->scene.camera.norm, m));
	}
	rt_data->render_next = false;
	render_frame(rt_data);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_rt_data	*rt_data;

	(void)keydata;
	rt_data = param;
	rt_data->render_next = true;
}

void	print_error(void)
{
	const t_error_data	error = rt_get_error_data();
	const char			*error_texts[] = {
	[E_NO_ERROR] = "lol, get rekt",
	[E_OPEN] = "Could not open file: ",
	[E_MALLOC] = "Malloc failed",
	[E_GNL] = "Failed to get next line",
	[E_EXPECTED_FLOAT] = "Expected float",
	[E_EXPECTED_INTEGER] = "Expected integer",
	[E_EXPECTED_IDENTIFIER] = "Expected identifier",
	[E_MLX] = "MLX Error",
	};

	ft_putstr_fd((char *)error_texts[error.error], STDOUT_FILENO);
	ft_putendl_fd((char *)error.data_text, STDOUT_FILENO);
}

uint32_t	rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (r << 24 | g << 16 | b << 8 | a << 0);
}

uint32_t	rgb(uint8_t r, uint8_t g, uint8_t b)
{
	return (rgba(r, g, b, 0xFF));
}

void	add_sphere(t_shape_list **list, t_vec3 pos, long double radius, int32_t rgb)
{
	t_sphere	sphere = {
		.coord = pos,
		.radius = radius,
		.rgb = rgb,
	};
	t_shape_list	*new_list = malloc(sizeof(t_shape_list));
	new_list->shape.type = SPHERE;
	new_list->shape.sphere = sphere;
	new_list->next = *list;
	*list = new_list;
}

void	add_plane(t_shape_list **list, t_vec3 pos, t_vec3 normal, int32_t rgb)
{
	t_plane	plane = {
		.coord = pos,
		.norm = normal,
		.rgb = rgb,
	};
	t_shape_list	*new_list = malloc(sizeof(t_shape_list));
	new_list->shape.type = PLANE;
	new_list->shape.plane = plane;
	new_list->next = *list;
	*list = new_list;
}

void	add_cylinder(t_shape_list **list, t_vec3 pos, t_vec3 normal, long double height, long double radius, int32_t rgb)
{
	t_cylinder	cylinder = {
		.coord = pos,
		.norm = normal,
		.rgb = rgb,
		.height = height,
		.radius = radius,
	};
	t_shape_list	*new_list = malloc(sizeof(t_shape_list));
	new_list->shape.type = CYLINDER;
	new_list->shape.cylinder = cylinder;
	new_list->next = *list;
	*list = new_list;
}

void	load_scene(t_scene *scene)
{
	scene->ambient.ratio = 0.4;
	scene->ambient.rgb = rgb(255, 255, 255);
	scene->camera.coord = vec3(0, 0, 0);
	scene->camera.fov = 90;
	scene->camera.norm = vec3(0, 0, 1);
	scene->light.brightness = 1;
	scene->light.coord = vec3(0, 0, 0);
	scene->light.rgb = rgb(255, 255, 255);
	scene->objects = NULL;
	add_sphere(&scene->objects, vec3(0, 0, 3), 1, rgb(255, 0, 0));
	// add_sphere(&scene->objects, vec3(1.5, 0, -3), 1, rgb(0, 0, 255));
	add_cylinder(&scene->objects, vec3(1.5, 0, 3), vec3(0, 1, 0), 2, 1, rgb(0, 0, 255));
	add_plane(&scene->objects, vec3(0, -0.5, 3), vec3(0, 1, 0), rgb(0, 255, 0));
}

int32_t	main(void)
{
	t_rt_data	rt_data;

	load_scene(&rt_data.scene);
	// if (parse_scene("test.rt", &scene) != OK)
	// {
	// 	print_error();
	// 	return (EXIT_FAILURE);
	// }
	rt_data.render_next = true;
	rt_data.width = 256;
	rt_data.height = 256;
	rt_data.mlx = mlx_init(rt_data.width, rt_data.height, "MLX42", true);
	if (rt_data.mlx == NULL)
		exit(EXIT_FAILURE);
	rt_data.image = mlx_new_image(rt_data.mlx, rt_data.width, rt_data.height);
	// memset(rt_data.image->pixels, 255, rt_data.image->width * rt_data.image->height * sizeof(int) / 2);
	mlx_image_to_window(rt_data.mlx, rt_data.image, 0, 0);
	mlx_loop_hook(rt_data.mlx, &loop_hook, &rt_data);
	mlx_key_hook(rt_data.mlx, &key_hook, &rt_data);
	mlx_loop(rt_data.mlx);
	mlx_terminate(rt_data.mlx);
	return (EXIT_SUCCESS);
}
