/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 11:09:03 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/09/22 12:47:31 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "utils/utils.h"
#include "input/input.h"
#include "render/render.h"
#include "movement.h"
#include <stdlib.h>

void	loop_hook(void *param)
{
	static bool	first_time = true;
	t_rt_data	*rt_data;

	rt_data = param;
	if (mlx_is_key_down(rt_data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(rt_data->mlx);
	if (try_movement(rt_data) || first_time)
		render_frame(rt_data);
	first_time = false;
}

static t_status	verify_args(int argc, char **argv)
{
	size_t	len;

	if (argc < 2)
		return (rt_set_error(E_TOO_FEW_ARGS, NULL));
	if (argc > 2)
		return (rt_set_error(E_TOO_MANY_ARGS, NULL));
	len = ft_strlen(argv[1]);
	if (len < 3 || ft_strncmp(argv[1] + ft_strlen(argv[1]) - 3, ".rt", 3) != 0)
		return (rt_set_error(E_EXPECTED_RT_FILE, NULL));
	return (OK);
}

static t_status	init_data(t_rt_data *rt_data)
{
	rt_data->scene.objects = NULL;
	rt_data->width = 256;
	rt_data->height = 256;
	rt_data->mlx = mlx_init(rt_data->width, rt_data->height,
			"miniRT [mvan-wij - rvan-duy]", true);
	if (rt_data->mlx == NULL)
		return (rt_set_error(E_MLX, (char *)mlx_strerror(mlx_errno)));
	rt_data->image = mlx_new_image(rt_data->mlx,
			rt_data->width, rt_data->height);
	if (rt_data->image == NULL)
		return (rt_set_error(E_MLX, (char *)mlx_strerror(mlx_errno)));
	if (mlx_image_to_window(rt_data->mlx, rt_data->image, 0, 0) < 0)
		return (rt_set_error(E_MLX, (char *)mlx_strerror(mlx_errno)));
	if (mlx_loop_hook(rt_data->mlx, &loop_hook, rt_data) == false)
		return (rt_set_error(E_MLX, (char *)mlx_strerror(mlx_errno)));
	return (OK);
}

int	main(int argc, char **argv)
{
	t_rt_data	rt_data;

	if (verify_args(argc, argv) != OK
		|| init_data(&rt_data) != OK
		|| parse_scene(argv[1], &rt_data.scene) != OK
	)
	{
		rt_print_error();
		return (EXIT_FAILURE);
	}
	mlx_loop(rt_data.mlx);
	mlx_terminate(rt_data.mlx);
	return (EXIT_SUCCESS);
}
