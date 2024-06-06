#include "miniRT.h"

bool solveQuadratic(float a, float b, float c, float *t0, float *t1)
{
    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return false;
    if (discriminant == 0)
    {
        *t0 = -0.5 * b / a;
        *t1 = *t0;
    }
    else
    {
        float sqrt_discriminant = sqrt(discriminant);
        *t0 = (-b - sqrt_discriminant) / (2 * a);
        *t1 = (-b + sqrt_discriminant) / (2 * a);
    }
    if (*t0 > *t1)
    {
        float temp = *t0;
        *t0 = *t1;
        *t1 = temp;
    }
    return true;
}

bool hit_cylinder_body(t_ray *ray, t_cy *cylinder, t_op *op, t_hit *hit)
{
    t_vec oc = subtract_vec(ray->origin, cylinder->coordinates);
    t_vec axis = normalize_vec(cylinder->normal);
    t_vec dir_cross_axis = cross_prod(ray->direction, axis);
    t_vec oc_cross_axis = cross_prod(oc, axis);
    
    op->a = dot_prod(dir_cross_axis, dir_cross_axis);
    op->b = 2 * dot_prod(dir_cross_axis, oc_cross_axis);
    op->c = dot_prod(oc_cross_axis, oc_cross_axis) - (cylinder->diameter / 2.0f) * (cylinder->diameter / 2.0f);
    if (!solveQuadratic(op->a, op->b, op->c, &op->t0, &op->t1))
        return false;
   	hit->t = op->t0;
    if (hit->t < 0)
    {
        hit->t = op->t1;
        if (hit->t < 0)
            return false;
    }
    hit->hit_point = add_vec(ray->origin, mult_by_scal(ray->direction, hit->t));
    t_vec to_hit = subtract_vec(hit->hit_point, cylinder->coordinates);
    float projection = dot_prod(to_hit, axis);
    if (projection < 0 || projection > cylinder->height)
        return false;
    t_vec base_to_hit = subtract_vec(to_hit, mult_by_scal(axis, projection));
    hit->normal = normalize_vec(base_to_hit);
    return true;
}

t_vec	ray_at(const t_ray *ray, double t)
{
	t_vec		dir;

	dir = ray->direction;
	dir = mult_by_scal(dir, t);
	return (add_vec(ray->origin, dir));
}

bool	hit_cylinder_caps(const t_ray *ray, t_disk *disk, t_hit *rec)
{
	double	denom;
	t_vec	oc;
	double	t;
	t_vec	p;
	t_vec	to_center;

	denom = dot_prod(disk->direction, ray->direction);
	if (fabs(denom) < 1e-6f)
		return (false);
	oc = subtract_vec(disk->coordinates, ray->origin);
	t = dot_prod(oc, disk->direction) / denom;
	if (t <= 1e-6f || t >= rec->t)
		return (false);
	p = ray_at(ray, t);
	to_center = subtract_vec(p, disk->coordinates);
	if (dot_prod(to_center, to_center) > disk->radius * disk->radius)
		return (false);
	rec->t = t;
	rec->hit_point = p;
	rec->normal = mult_by_scal(disk->direction, -1);
	return (true);
}

bool hit_cylinder(t_ray *ray, t_cy *cylinder, t_vec *hit_point, t_vec *normal)
{
    t_op op;
	t_hit hitt;
    bool hit = false;
	t_disk disk;

    disk.coordinates = cylinder->coordinates;
	disk.direction = cylinder->normal;
	disk.radius = cylinder->diameter / 2;
	hitt.hit_point = new_vec(0, 0, 0);
	hitt.normal = new_vec(0,0,0);
    hitt.t = INFINITY;
	if (hit_cylinder_caps(ray, &disk, &hitt))
    {
        *hit_point = hitt.hit_point;
        *normal = hitt.normal;
        hit = true;
    }
	disk.coordinates = add_vec(cylinder->coordinates, mult_by_scal(normalize_vec(cylinder->normal), cylinder->height));
	disk.direction = mult_by_scal(cylinder->normal, -1);
	if (hit_cylinder_caps(ray, &disk, &hitt))
    {
        *hit_point = hitt.hit_point;
        *normal = hitt.normal;
        hit = true;
    }
    if (hit_cylinder_body(ray, cylinder, &op, &hitt))
    {
        *hit_point = hitt.hit_point;
        *normal = hitt.normal;
        hit = true;
    }
    return hit;
}
