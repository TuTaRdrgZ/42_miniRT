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

bool hit_cylinder_body(t_ray *ray, t_cy *cylinder, t_op *op, t_vec *hit_point, t_vec *normal)
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
    float t = op->t0;
    if (t < 0)
    {
        t = op->t1;
        if (t < 0)
            return false;
    }
    *hit_point = add_vec(ray->origin, mult_by_scal(ray->direction, t));
    t_vec to_hit = subtract_vec(*hit_point, cylinder->coordinates);
    float projection = dot_prod(to_hit, axis);
    if (projection < 0 || projection > cylinder->height)
        return false;
    t_vec base_to_hit = subtract_vec(to_hit, mult_by_scal(axis, projection));
    *normal = normalize_vec(base_to_hit);
    return true;
}

bool hit_cylinder_caps(t_ray *ray, t_cy *cylinder, t_vec *hit_point, t_vec *normal, float *t)
{
    t_vec top_center = add_vec(cylinder->coordinates, mult_by_scal(cylinder->normal, cylinder->height));
    t_vec cap_normal = normalize_vec(cylinder->normal);
    float denom = dot_prod(ray->direction, cap_normal);
    
    if (fabs(denom) > 1e-6)
    {
        float t_cap = dot_prod(subtract_vec(cylinder->coordinates, ray->origin), cap_normal) / denom;
        if (t_cap >= 0)
        {
            t_vec hit = add_vec(ray->origin, mult_by_scal(ray->direction, t_cap));
            if (length_vec(subtract_vec(hit, cylinder->coordinates)) <= (cylinder->diameter / 2.0f))
            {
                if (t_cap < *t)
                {
                    *t = t_cap;
                    *hit_point = hit;
                    *normal = cap_normal;
                    return true;
                }
            }
        }

        t_cap = dot_prod(subtract_vec(top_center, ray->origin), cap_normal) / denom;
        if (t_cap >= 0)
        {
            t_vec hit = add_vec(ray->origin, mult_by_scal(ray->direction, t_cap));
            if (length_vec(subtract_vec(hit, top_center)) <= (cylinder->diameter / 2.0f))
            {
                if (t_cap < *t)
                {
                    *t = t_cap;
                    *hit_point = hit;
                    *normal = cap_normal;
                    return true;
                }
            }
        }
    }
    return false;
}

bool hit_cylinder(t_ray *ray, t_cy *cylinder, t_vec *hit_point, t_vec *normal)
{
    t_op op;
    float t = INFINITY;
    t_vec temp_hit_point, temp_normal;
    bool hit = false;

    if (hit_cylinder_body(ray, cylinder, &op, &temp_hit_point, &temp_normal))
    {
        t = op.t0;
        *hit_point = temp_hit_point;
        *normal = temp_normal;
        hit = true;
    }

    if (hit_cylinder_caps(ray, cylinder, &temp_hit_point, &temp_normal, &t))
    {
        *hit_point = temp_hit_point;
        *normal = temp_normal;
        hit = true;
    }

    return hit;
}
