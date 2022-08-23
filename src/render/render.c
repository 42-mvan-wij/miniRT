/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 15:12:03 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/08/23 17:39:31 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "structs.h"
#include <math.h>

typedef struct s_ray {
	t_vec3	dir;
	t_vec3	origin;
	t_vec3	rgb_energy;
}	t_ray;

t_vec3	vec3(long double x, long double y, long double z)
{
	t_vec3	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_vec3	cross(t_vec3 v1, t_vec3 v2)
{
	return (vec3(
			v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x));
}

t_vec3	scale(t_vec3 v, long double scalar)
{
	return (vec3(
			v.x * scalar,
			v.y * scalar,
			v.z * scalar));
}

t_vec3	add(t_vec3 v1, t_vec3 v2)
{
	return (vec3(
			v1.x + v2.x,
			v1.y + v2.y,
			v1.z + v2.z));
}

t_vec3	sub(t_vec3 v1, t_vec3 v2)
{
	return (vec3(
			v1.x - v2.x,
			v1.y - v2.y,
			v1.z - v2.z));
}

long double	mag2(t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

long double	mag(t_vec3 v)
{
	return (sqrt(mag2(v)));
}

long double dist2(t_vec3 v1, t_vec3 v2)
{
	return (mag2(sub(v1, v2)));
}

long double	dist(t_vec3 v1, t_vec3 v2)
{
	return (sqrt(dist2(v1, v2)));
}

t_vec3	normalize(t_vec3 v)
{
	return (scale(v, 1 / mag(v)));
}

bool	almost_equal(long double a, long double b)
{
	long double	diff;

	diff = a - b;
	return (diff <= __DBL_EPSILON__ || diff >= -__DBL_EPSILON__);
}

void	set_ray(t_ray *ray, long double x, long double y, t_rt_data *rt_data)
{
	long double	scalar;
	t_vec3		right;
	t_vec3		down;
	double		px;
	double		py;

	scalar = tan(rt_data->scene->camera.fov * 0.5);
	px = (2 * x + 1 - rt_data->width) * scalar;
	py = (2 * y + 1 - rt_data->height) * scalar;
	if (almost_equal(rt_data->scene->camera.norm.x, 0) \
	&& almost_equal(rt_data->scene->camera.norm.z, 0))
		right = vec3(1, 0, 0);
	else
		right = cross(vec3(0, 1, 0), rt_data->scene->camera.norm);
	down = cross(rt_data->scene->camera.norm, right);
	ray->dir = normalize(add(add(
					scale(right, px),
					scale(down, py)),
				scale(rt_data->scene->camera.norm, rt_data->height)));
	ray->origin = rt_data->scene->camera.coord;
	ray->rgb_energy = vec3(1, 1, 1);
}

#define MAX_BOUNCES 8

int	vec2color(t_vec3 v)
{
	int	r;
	int	g;
	int	b;

	r = v.x * 255;
	g = v.y * 255;
	b = v.z * 255;
	return (r << 16 | g << 8 | b);
}

typedef struct s_rayhit {
	t_vec3		pos;
	long double	distance2;
	t_vec3		normal;
}	t_rayhit;

typedef struct	s_shape_list {
	struct s_shape_list	*next;
	t_object			shape;
}	t_shape_list;

void	init_rayhit(t_rayhit *rayhit)
{
	rayhit->distance2 = INFINITY;
	rayhit->pos = vec3(0, 0, 0);
	rayhit->normal = vec3(0, 0, 0);
}

void	intersect_sphere(t_ray ray, t_rayhit *best_hit, t_sphere *sphere)
{
	if (dist2(ray.origin, sphere->coord) - sphere->radius * sphere->radius >= best_hit->distance2)
		return ;
}

void	intersect(t_ray ray, t_rayhit *best_hit, t_object *shape)
{
	if (shape->type == SPHERE)
		intersect_sphere(ray, best_hit, &shape->sphere);
	if (shape->type == PLANE)
		intersect_plane(ray, best_hit, &shape->plane);
	if (shape->type == CYLINDER)
		intersect_cylinder(ray, best_hit, &shape->cylinder);
}

t_rayhit	trace(t_ray ray, t_shape_list *shapes)
{
	t_rayhit	best_hit;

	init_rayhit(&best_hit);
	while (shapes != NULL)
	{
		intersect(ray, &best_hit, &shapes->shape);
		shapes = shapes->next;
	}
}

void	render_line(t_rt_data *rt_data, int y)
{
	int			x;
	t_vec3		color;
	int			i;
	t_ray		ray;
	t_rayhit	hit;

	x = 0;
	while (x < rt_data->width)
	{
		set_ray(&ray, x, y, rt_data);
		color = vec3(0, 0, 0);
		i = 0;
		while (i < MAX_BOUNCES)
		{
			hit = trace(ray, rt_data->scene);
			i++;
		}
		mlx_put_pixel(rt_data->image, x, y, vec2color(color));
		x++;
	}
}

void	render_frame(t_rt_data *rt_data)
{
	int	y;

	y = 0;
	while (y < rt_data->height)
	{
		render_line(rt_data, y);
		y++;
	}
}
