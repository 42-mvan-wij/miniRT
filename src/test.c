/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 15:32:30 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/08/27 14:14:40 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>

#include "libft.h"
#include "structs.h"
#include "input/input.h"
#include "utils/utils.h"

#define WIDTH 256
#define HEIGHT 256

mlx_image_t	*g_img;

void	hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(param, MLX_KEY_ESCAPE))
		mlx_close_window(param);
	if (mlx_is_key_down(param, MLX_KEY_UP))
		g_img->instances[0].y -= 5;
	if (mlx_is_key_down(param, MLX_KEY_DOWN))
		g_img->instances[0].y += 5;
	if (mlx_is_key_down(param, MLX_KEY_LEFT))
		g_img->instances[0].x -= 5;
	if (mlx_is_key_down(param, MLX_KEY_RIGHT))
		g_img->instances[0].x += 5;
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
	};

	ft_putstr_fd((char *)error_texts[error.error], STDOUT_FILENO);
	ft_putendl_fd((char *)error.data_text, STDOUT_FILENO);
}

int32_t	main(int argc, char **argv)
{
	mlx_t	*mlx;
	t_scene	scene;

	(void)argc;
	// TODO: check valid file
	if (parse_scene(argv[1], &scene) != OK)
	{
		print_error();
		return (EXIT_FAILURE);
	}
	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	g_img = mlx_new_image(mlx, 128, 128);
	memset(g_img->pixels, 255, g_img->width * g_img->height * sizeof(int));
	mlx_image_to_window(mlx, g_img, 0, 0);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
