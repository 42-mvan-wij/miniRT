/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 12:42:23 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/09/22 12:44:39 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "vec3/vec3.h"
#include <MLX42.h>
#include <math.h>

static bool	try_move(t_rt_data *rt_data, keys_t key, t_vec3 dir,
				long double amount)
{
	if (!mlx_is_key_down(rt_data->mlx, key))
		return (false);
	rt_data->scene.camera.pos = add(
			rt_data->scene.camera.pos, scale(dir, amount));
	return (true);
}

static bool	try_pitch(t_rt_data *rt_data, keys_t key, long double amount)
{
	if (!mlx_is_key_down(rt_data->mlx, key))
		return (false);
	rt_data->scene.camera.norm = normalize(rot(rt_data->scene.camera.norm,
				normalize(cross(vec3(0, 1, 0), rt_data->scene.camera.norm)),
				amount));
	return (true);
}

static bool	try_yaw(t_rt_data *rt_data, keys_t key, long double amount)
{
	const t_matrix	m = {
		.data = {
		cosl(amount), 0, -sinl(amount),
		0, 1, 0,
		sinl(amount), 0, cosl(amount)
	}};

	if (!mlx_is_key_down(rt_data->mlx, key))
		return (false);
	rt_data->scene.camera.norm = normalize(
			transform(rt_data->scene.camera.norm, m));
	return (true);
}

bool	try_movement(t_rt_data *rt_data)
{
	static long double	speed = MOVEMENT_SPEED;
	t_vec3				forward;
	t_vec3				right;
	t_vec3				up;
	bool				moved;

	up = vec3(0, 1, 0);
	if (vec3_eq(up, rt_data->scene.camera.norm))
		right = vec3(1, 0, 0);
	else
		right = normalize(cross(vec3(0, 1, 0), rt_data->scene.camera.norm));
	forward = cross(right, up);
	moved = try_move(rt_data, MLX_KEY_LEFT_SHIFT, up, -(speed));
	if (!moved)
		moved = (try_move(rt_data, MLX_KEY_RIGHT_SHIFT, up, -(speed)) || moved);
	moved = (try_move(rt_data, MLX_KEY_SPACE, up, speed) || moved);
	moved = (try_move(rt_data, MLX_KEY_W, forward, speed) || moved);
	moved = (try_move(rt_data, MLX_KEY_A, right, -(speed)) || moved);
	moved = (try_move(rt_data, MLX_KEY_S, forward, -(speed)) || moved);
	moved = (try_move(rt_data, MLX_KEY_D, right, speed) || moved);
	moved = (try_pitch(rt_data, MLX_KEY_UP, -0.1 * speed) || moved);
	moved = (try_pitch(rt_data, MLX_KEY_DOWN, 0.1 * speed) || moved);
	moved = (try_yaw(rt_data, MLX_KEY_LEFT, -0.1 * speed) || moved);
	moved = (try_yaw(rt_data, MLX_KEY_RIGHT, 0.1 * speed) || moved);
	return (moved);
}
