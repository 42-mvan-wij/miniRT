/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 15:12:03 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/08/31 12:58:42 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "structs.h"
#include <math.h>
#include <stdio.h> // FIXME: TMP

typedef uint32_t	t_color;

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

t_vec3	rot(t_vec3 v, t_vec3 axis, long double angle)
{
	const long double	cos_a = cosl(angle);

	return (add(add(
				scale(axis, (1 - cos_a) * dot(v, axis)),
				scale(v, cos_a)),
			scale(cross(axis, v), sinl(angle))));
}

bool	almost_equal(long double a, long double b)
{
	long double	diff;

	diff = a - b;
	return (diff <= __DBL_EPSILON__ * 10 && diff >= -__DBL_EPSILON__ * 10);
}

void	set_ray(t_ray *ray, long double x, long double y, t_rt_data *rt_data)
{
	unsigned width = rt_data->width, height = rt_data->height;
	float inv_width = 1.0 / (long double)width, inv_height = 1.0 / (long double)height;
	float fov = rt_data->scene.camera.fov;
	float aspect_ratio = (long double)width / (long double)height;
	float angle = tanl(M_PI * 0.5 * fov / 180.0);

	float xx = (2 * ((x + 0.5) * inv_width) - 1) * angle * aspect_ratio;
	float yy = (1 - 2 * ((y + 0.5) * inv_height)) * angle;
	t_vec3	right;
	if (almost_equal(rt_data->scene.camera.norm.y, 1))
		right = vec3(1, 0, 0);
	else
		right = cross(vec3(0, 1, 0), rt_data->scene.camera.norm);
	t_vec3	up = cross(rt_data->scene.camera.norm, right);
	// ray->dir = normalize(vec3(xx, yy, 1));
	ray->dir = normalize(add(rt_data->scene.camera.norm, add(
		scale(up, yy),
		scale(right, xx)
	)));
	ray->origin = rt_data->scene.camera.coord;
	ray->rgb_energy = vec3(1, 1, 1);
}

t_color	vec2color(t_vec3 v)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	if (v.x > 1)
		r = 255;
	else if (v.x < 0)
		r = 0;
	else
		r = v.x * 255;
	if (v.y > 1)
		g = 255;
	else if (v.y < 0)
		g = 0;
	else
		g = v.y * 255;
	if (v.z > 1)
		b = 255;
	else if (v.z < 0)
		b = 0;
	else
		b = v.z * 255;
	a = 255;
	return (r << 24 | g << 16 | b << 8 | a << 0);
}

t_vec3	color2vec(t_color c)
{
	return (scale(vec3(
				(c >> 24) & 0xFF,
				(c >> 16) & 0xFF,
				(c >> 8) & 0xFF), 1.0 / 255.0));
}

typedef struct s_rayhit {
	long double		distance;
	t_vec3			normal;
	t_object		*shape;
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
void	intersect_sphere(t_ray ray, t_rayhit *best_hit, t_object *shape)
{
	long double	t[2];
	long double	tt;

	if (!intersect_sphere_comp(ray, shape->sphere.coord, shape->sphere.radius, t))
		return ;
	tt = t[0];
	if (tt < 0)
		tt = t[1];
	if (tt >= best_hit->distance)
		return ;
	best_hit->distance = tt;
	best_hit->normal = normalize(sub(add(ray.origin, scale(ray.dir, tt)), shape->sphere.coord));
	best_hit->shape = shape;
}

void	intersect_plane(t_ray ray, t_rayhit *best_hit, t_object *shape)
{
	const long double	a = dot(ray.dir, shape->plane.norm);
	double				t;

	if (almost_equal(a, 0))
		return ;
	t = dot(shape->plane.norm, sub(shape->plane.coord, ray.origin)) / a;
	if (t < 0 || t >= best_hit->distance)
		return ;
	best_hit->distance = t;
	best_hit->normal = shape->plane.norm;
	best_hit->shape = shape;
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

void	intersect_cylinder(t_ray ray, t_rayhit *best_hit, t_object *shape)
{
	t_ray		pers_ray;
	t_ray		flat_ray;
	long double	t[2];
	long double	tt;

	pers_ray = in_cylinder_perspective(ray, &shape->cylinder);
	flat_ray.origin = vec3(pers_ray.origin.x, 0, pers_ray.origin.z);
	flat_ray.dir = normalize(vec3(pers_ray.dir.x, 0, pers_ray.dir.z));
	flat_ray.rgb_energy = ray.rgb_energy; // not really needed
	if (!intersect_sphere_comp(flat_ray, vec3(0, 0, 0), shape->cylinder.radius, t))
		return ;
	tt = t[0] / dot(pers_ray.dir, flat_ray.dir);
	if (tt < 0 || pers_ray.dir.y * tt + pers_ray.origin.y < -shape->cylinder.height / 2 || pers_ray.dir.y * tt + pers_ray.origin.y > shape->cylinder.height / 2)
	{
		tt = t[1] / dot(pers_ray.dir, flat_ray.dir);
		if (pers_ray.dir.y * tt + pers_ray.origin.y < -shape->cylinder.height / 2 || pers_ray.dir.y * tt + pers_ray.origin.y > shape->cylinder.height / 2)
			return ;
	}
	if (tt >= best_hit->distance)
		return ;
	best_hit->distance = tt;
	best_hit->normal = get_cylinder_normal(ray, &shape->cylinder, tt);
	best_hit->shape = shape;
}

void	intersect(t_ray ray, t_rayhit *best_hit, t_object *shape)
{
	if (shape->type == SPHERE)
		intersect_sphere(ray, best_hit, shape);
	if (shape->type == PLANE)
		intersect_plane(ray, best_hit, shape);
	if (shape->type == CYLINDER)
		intersect_cylinder(ray, best_hit, shape);
}

bool	vec3_eq(t_vec3 v1, t_vec3 v2)
{
	// return (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z);
	return (almost_equal(v1.x, v2.x) && almost_equal(v1.y, v2.y) && almost_equal(v1.z, v2.z));
}

t_rayhit	trace(t_ray ray, t_shape_list *shapes, t_rayhit *ignore)
{
	t_rayhit	old_hit;
	t_rayhit	best_hit;

	init_rayhit(&best_hit);
	while (shapes != NULL)
	{
		if (ignore != NULL && &shapes->shape == ignore->shape)
		{
			old_hit = best_hit;
			intersect(ray, &best_hit, &shapes->shape);
			if (best_hit.shape == ignore->shape && vec3_eq(best_hit.normal, ignore->normal))
				best_hit = old_hit;
		}
		else
			intersect(ray, &best_hit, &shapes->shape);
		shapes = shapes->next;
	}
	return (best_hit);
}

t_vec3	scale_color(t_vec3 color1, t_vec3 color2)
{
	return (vec3(
			color1.x * color2.x,
			color1.y * color2.y,
			color1.z * color2.z));
}

t_vec3	get_shape_color(t_object *shape)
{
	if (shape->type == SPHERE)
		return (color2vec(shape->sphere.rgb));
	if (shape->type == PLANE)
		return (color2vec(shape->plane.rgb));
	if (shape->type == CYLINDER)
		return (color2vec(shape->cylinder.rgb));
	return (vec3(0, 0, 0));
}

t_vec3	adjust_color(t_vec3 color, t_rayhit hit, t_ray ray, t_rt_data *rt_data)
{
	t_ray	light_ray;
	t_vec3	diff;

	if (hit.distance >= INFINITY)
		return (color);
	color = add(color, scale(scale_color(color2vec(rt_data->scene.ambient.rgb), get_shape_color(hit.shape)), rt_data->scene.ambient.ratio));
	light_ray.origin = add(ray.origin, scale(ray.dir, hit.distance));
	diff = sub(rt_data->scene.light.coord, light_ray.origin);
	light_ray.dir = normalize(diff);
	t_rayhit new_hit = trace(light_ray, rt_data->scene.objects, &hit);
	(void)new_hit;
	if (new_hit.distance * new_hit.distance >= mag2(diff))
	{
		long double cos_a = dot(light_ray.dir, hit.normal);
		if (cos_a < 0)
			return (color);
		t_vec3 effect = scale(scale(color2vec(rt_data->scene.light.rgb), cos_a), 1.0 / (mag(diff) + hit.distance) * (mag(diff) + hit.distance));
		long double mattness = 1; // kappa * dot(normal, ray.dir);
		// glossyness;
		color = add(color,
			scale(scale_color(
				scale(
					scale(effect, mattness), 1//20.0 / (hit.distance * hit.distance)
				), get_shape_color(hit.shape)
			), rt_data->scene.light.brightness)
		);
	}
	return (color);
}

#define MAX_BOUNCES 8

t_color	get_pixel_color(t_rt_data *rt_data, int x, int y)
{
	t_vec3		color;
	int			i;
	t_ray		ray;
	t_rayhit	hit;

	set_ray(&ray, x, y, rt_data);
	color = vec3(0, 0, 0);
	i = 0;
	// while (i < MAX_BOUNCES)
	{
		hit = trace(ray, rt_data->scene.objects, NULL);
		// color = vec3(fabsl(hit.normal.x), fabsl(hit.normal.y), fabsl(hit.normal.z));
		color = adjust_color(color, hit, ray, rt_data);
		i++;
	}
	return (vec2color(color));
}

void	render_frame(t_rt_data *rt_data)
{
	int		y;
	int		x;
	t_color	color;

	y = 0;
	while (y < rt_data->height)
	{
		x = 0;
		while (x < rt_data->width)
		{
			color = get_pixel_color(rt_data, x, y);
			mlx_put_pixel(rt_data->image, x, y, color);
			x++;
		}
		y++;
	}
}
