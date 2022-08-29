/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 15:12:03 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/08/29 11:27:03 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "structs.h"
#include <math.h>
#include <stdio.h> // FIXME: TMP

typedef struct s_ray {
	t_vec3	dir;
	t_vec3	origin;
	t_vec3	rgb_energy;
}	t_ray;

typedef struct s_matrix {
	long double	data[3 * 3];
}	t_matrix;

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

// project v1 onto v2 and multiply length by length of v2, order doesn't matter
long double	dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x
		+ v1.y * v2.y
		+ v1.z * v2.z);
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
	return (sqrtl(mag2(v)));
}

long double dist2(t_vec3 v1, t_vec3 v2)
{
	return (mag2(sub(v1, v2)));
}

long double	dist(t_vec3 v1, t_vec3 v2)
{
	return (sqrtl(dist2(v1, v2)));
}

t_vec3	normalize(t_vec3 v)
{
	return (scale(v, 1 / mag(v)));
}

t_matrix	matrix_from_vecs(t_vec3 right, t_vec3 up, t_vec3 in)
{
	const t_matrix	matrix = {
		.data = {
		right.x, up.x, in.x,
		right.y, up.y, in.y,
		right.z, up.z, in.z,
	}};

	return (matrix);
}

t_matrix	matrix_dot(t_matrix m1, t_matrix m2)
{
	const t_matrix	matrix = {
		.data = {
		m1.data[0 + 0 * 3] * m2.data[0 + 0 * 3] + m1.data[1 + 0 * 3]
		* m2.data[0 + 1 * 3] + m1.data[2 + 0 * 3] * m2.data[0 + 2 * 3],
		m1.data[0 + 0 * 3] * m2.data[1 + 0 * 3] + m1.data[1 + 0 * 3]
		* m2.data[1 + 1 * 3] + m1.data[2 + 0 * 3] * m2.data[1 + 2 * 3],
		m1.data[0 + 0 * 3] * m2.data[2 + 0 * 3] + m1.data[1 + 0 * 3]
		* m2.data[2 + 1 * 3] + m1.data[2 + 0 * 3] * m2.data[2 + 2 * 3],

		m1.data[0 + 1 * 3] * m2.data[0 + 0 * 3] + m1.data[1 + 1 * 3]
		* m2.data[0 + 1 * 3] + m1.data[2 + 1 * 3] * m2.data[0 + 2 * 3],
		m1.data[0 + 1 * 3] * m2.data[1 + 0 * 3] + m1.data[1 + 1 * 3]
		* m2.data[1 + 1 * 3] + m1.data[2 + 1 * 3] * m2.data[1 + 2 * 3],
		m1.data[0 + 1 * 3] * m2.data[2 + 0 * 3] + m1.data[1 + 1 * 3]
		* m2.data[2 + 1 * 3] + m1.data[2 + 1 * 3] * m2.data[2 + 2 * 3],

		m1.data[0 + 2 * 3] * m2.data[0 + 0 * 3] + m1.data[1 + 2 * 3]
		* m2.data[0 + 1 * 3] + m1.data[2 + 2 * 3] * m2.data[0 + 2 * 3],
		m1.data[0 + 2 * 3] * m2.data[1 + 0 * 3] + m1.data[1 + 2 * 3]
		* m2.data[1 + 1 * 3] + m1.data[2 + 2 * 3] * m2.data[1 + 2 * 3],
		m1.data[0 + 2 * 3] * m2.data[2 + 0 * 3] + m1.data[1 + 2 * 3]
		* m2.data[2 + 1 * 3] + m1.data[2 + 2 * 3] * m2.data[2 + 2 * 3],
	}};

	return (matrix);
}

t_matrix	compose(t_matrix m1, t_matrix m2)
{
	return (matrix_dot(m2, m1));
}

t_vec3	transform(t_vec3 v, t_matrix m)
{
	return (vec3(
			v.x * m.data[0 + 0 * 3] + v.y * m.data[0 + 1 * 3]
			+ v.z * m.data[0 + 2 * 3],
			v.x * m.data[1 + 0 * 3] + v.y * m.data[1 + 1 * 3]
			+ v.z * m.data[1 + 2 * 3],
			v.x * m.data[2 + 0 * 3] + v.y * m.data[2 + 1 * 3]
			+ v.z * m.data[2 + 2 * 3]));
}

bool	almost_equal(long double a, long double b)
{
	long double	diff;

	diff = a - b;
	return (diff <= __DBL_EPSILON__ && diff >= -__DBL_EPSILON__);
}

void	set_ray(t_ray *ray, long double x, long double y, t_rt_data *rt_data)
{
	long double	scalar;
	t_vec3		right;
	t_vec3		down;
	double		px;
	double		py;

	scalar = tan(rt_data->scene.camera.fov * 0.5);
	px = (2 * x + 1 - rt_data->width) * scalar;
	py = (2 * y + 1 - rt_data->height) * scalar;
	if (almost_equal(rt_data->scene.camera.norm.x, 0) \
	&& almost_equal(rt_data->scene.camera.norm.z, 0))
		right = vec3(1, 0, 0);
	else
		right = cross(vec3(0, 1, 0), rt_data->scene.camera.norm);
	down = cross(right, rt_data->scene.camera.norm);
	ray->dir = normalize(add(add(
					scale(right, px),
					scale(down, py)),
				scale(rt_data->scene.camera.norm, rt_data->height)));
	ray->origin = rt_data->scene.camera.coord;
	ray->rgb_energy = vec3(1, 1, 1);
}

#define MAX_BOUNCES 8

int	vec2color(t_vec3 v)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	r = v.x * 255;
	g = v.y * 255;
	b = v.z * 255;
	a = 255;
	return (r << 24 | g << 16 | b << 8 | a << 0);
}

typedef struct s_rayhit {
	long double		distance;
	t_vec3			normal;
	t_object_type	type;
	union
	{
		t_sphere	*sphere;
		t_plane		*plane;
		t_cylinder	*cylinder;
	};
}	t_rayhit;

void	init_rayhit(t_rayhit *rayhit)
{
	rayhit->distance = INFINITY;
	rayhit->normal = vec3(0, 0, 0);
}

bool	intersect_sphere_comp(t_ray ray, t_vec3 origin, long double radius, long double t[2])
{
	const t_vec3		diff = sub(origin, ray.origin); // d
	const long double	tc = dot(diff, ray.dir); // p1
	long double			d2;
	long double			t1c; // p2

	d2 = mag2(diff) - tc * tc;
	if (d2 > radius * radius)
		return (false);
	t1c = sqrtl(radius * radius - d2);
	t[0] = tc - t1c;
	t[1] = tc + t1c;
	if (t[1] < 0)
		return (false);
	return (true);
}

// https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
// http://kylehalladay.com/blog/tutorial/math/2013/12/24/Ray-Sphere-Intersection.html
void	intersect_sphere(t_ray ray, t_rayhit *best_hit, t_sphere *sphere)
{
	long double	t[2];
	long double	tt;

	if (!intersect_sphere_comp(ray, sphere->coord, sphere->radius, t))
		return ;
	tt = t[0];
	if (tt < 0)
		tt = t[1];
	if (tt >= best_hit->distance)
		return ;
	best_hit->distance = tt;
	best_hit->normal = normalize(sub(add(ray.origin, scale(ray.dir, tt)), sphere->coord));
	best_hit->type = SPHERE;
	best_hit->sphere = sphere;
}

void	intersect_plane(t_ray ray, t_rayhit *best_hit, t_plane *plane)
{
	const long double volatile	a = dot(ray.dir, plane->norm);
	double				t;

	if (almost_equal(a, 0))
		return ;
	t = dot(plane->norm, sub(plane->coord, ray.origin)) / a;
	if (t < 0 || t >= best_hit->distance)
		return ;
	best_hit->distance = t;
	best_hit->normal = plane->norm;
	best_hit->type = PLANE;
	best_hit->plane = plane;
}

long double	sin_from_cos(long double cos_a)
{
	return (sinl(acosl(cos_a)));
	// return (sqrtl(1 - (cos_a * cos_a)));
}

t_vec3	get_cylinder_normal(t_ray ray, t_cylinder *cylinder, long double t)
{
	t_vec3	point;
	t_vec3	dir;

	point = add(scale(ray.dir, t), ray.origin);
	dir = sub(point, cylinder->coord);
	return (normalize(cross(cross(cylinder->norm, dir), cylinder->norm)));
}

#define COS 0
#define SIN 1

t_ray	in_cylinder_perspective(t_ray ray, t_cylinder *cylinder)
{
	t_vec3		flat_normal;
	long double	cos_sin_a[2];
	long double	cos_sin_b[2];
	t_matrix	m;
	t_ray		out_ray;

	if (almost_equal(cylinder->norm.y, 1))
		m = matrix_from_vecs(vec3(1, 0, 0), vec3(0, 1, 0), vec3(0, 0, 1));
	else
	{
		flat_normal = cylinder->norm;
		flat_normal.y = 0;
		cos_sin_a[COS] = dot(vec3(1, 0, 0), flat_normal) / mag(flat_normal);
		cos_sin_a[SIN] = sin_from_cos(cos_sin_a[COS]);
		cos_sin_b[COS] = dot(vec3(0, 1, 0), cylinder->norm);
		cos_sin_b[SIN] = sin_from_cos(cos_sin_b[COS]);
		m = compose(
				matrix_from_vecs(vec3(cos_sin_a[COS], 0, -cos_sin_a[SIN]),
					vec3(0, 1, 0), vec3(cos_sin_a[SIN], 0, cos_sin_a[COS])),
				matrix_from_vecs(vec3(-cos_sin_b[SIN], cos_sin_b[COS], 0),
					vec3(cos_sin_b[COS], cos_sin_b[SIN], 0), vec3(0, 0, 1)));
	}
	out_ray.rgb_energy = ray.rgb_energy; // not really needed
	out_ray.dir = transform(ray.dir, m);
	out_ray.origin = transform(sub(ray.origin, cylinder->coord), m);
	return (out_ray);
}

void	intersect_cylinder(t_ray ray, t_rayhit *best_hit, t_cylinder *cylinder)
{
	t_ray		pers_ray;
	t_ray		flat_ray;
	long double	t[2];
	long double	tt;

	pers_ray = in_cylinder_perspective(ray, cylinder);
	flat_ray.origin = vec3(pers_ray.origin.x, 0, pers_ray.origin.z);
	flat_ray.dir = normalize(vec3(pers_ray.dir.x, 0, pers_ray.dir.z));
	flat_ray.rgb_energy = ray.rgb_energy; // not really needed
	if (!intersect_sphere_comp(flat_ray, vec3(0, 0, 0), cylinder->radius, t))
		return ;
	tt = t[0];
	if (tt < 0 || pers_ray.dir.y * tt + pers_ray.origin.y < -cylinder->height / 2 || pers_ray.dir.y * tt + pers_ray.origin.y > cylinder->height / 2)
	{
		tt = t[1];
		if (pers_ray.dir.y * tt + pers_ray.origin.y < -cylinder->height / 2 || pers_ray.dir.y * tt + pers_ray.origin.y > cylinder->height / 2)
			return ;
	}
	if (tt >= best_hit->distance)
		return ;
	best_hit->distance = tt;
	best_hit->normal = get_cylinder_normal(ray, cylinder, tt);
	best_hit->type = CYLINDER;
	best_hit->cylinder = cylinder;
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
	return (best_hit);
}

void	render_line(t_rt_data *rt_data, int y)
{
	int			x;
	t_vec3		color;
	int			i;
	t_ray		ray;
	t_rayhit	hit;
	int			final_color;

	x = 0;
	while (x < rt_data->width)
	{
		set_ray(&ray, x, y, rt_data);
		final_color = 0x000000FF;
		// color = vec3(0, 0, 0);
		i = 0;
		while (i < MAX_BOUNCES)
		{
			hit = trace(ray, rt_data->scene.objects);
			// printf("type: %i\n", hit.type);
			if (hit.distance != INFINITY)
			{
				// printf("hit something\n");
				// (void)color;
				// if (hit.type == SPHERE)
				// 	final_color = hit.sphere->rgb;
				// if (hit.type == PLANE)
				// 	final_color = hit.plane->rgb;
				// if (hit.type == CYLINDER)
				// 	final_color = hit.cylinder->rgb;
				color.x = fabsl(hit.normal.x);
				color.y = fabsl(hit.normal.y);
				color.z = fabsl(hit.normal.z);
				final_color = vec2color(color);
			}
			i++;
			break;
		}
		mlx_put_pixel(rt_data->image, x, y, final_color);
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
