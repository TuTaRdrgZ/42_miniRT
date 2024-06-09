/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 17:17:34 by bautrodr          #+#    #+#             */
/*   Updated: 2024/06/09 18:13:34 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	solve_quadratic(t_op *op)
{
	float	discriminant;
	float	sqrt_discriminant;
	float	temp;

	discriminant = op->b * op->b - 4.0f * op->a * op->c;
	if (discriminant < 0.0f)
		return (false);
	else if (discriminant == 0.0f)
	{
		op->t1 = -(op->b) / (2.0f * op->a);
		op->t0 = op->t1;
	}
	else
	{
		sqrt_discriminant = sqrt(discriminant);
		op->t0 = (-(op->b) + sqrt_discriminant) / (2.0f * op->a);
		op->t1 = (-(op->b) - sqrt_discriminant) / (2.0f * op->a);
	}
	if (op->t0 > op->t1)
	{
		temp = op->t0;
		op->t0 = op->t1;
		op->t1 = temp;
	}
	return (true);
}

static void	set_hit(t_ray *ray, t_sp *sphere, t_hit *hit, t_op *op)
{
	hit->hit_point = add_vec(ray->origin, mult_by_scal(ray->direction, op->t0));
	hit->normal = subtract_vec(hit->hit_point, sphere->coordinates);
	hit->normal = normalize_vec(hit->normal);
}

bool	hit_sphere(t_ray *ray, t_sp *sphere, t_hit *hit)
{
	t_vec	l;
	t_op	op;

	l = subtract_vec(ray->origin, sphere->coordinates);
	op.a = dot_prod(ray->direction, ray->direction);
	op.b = 2.0f * dot_prod(ray->direction, l);
	op.c = dot_prod(l, l) - sphere->radius * sphere->radius;
	if (!solve_quadratic(&op))
		return (false);
	if (op.t0 > op.t1)
	{
		op.temp = op.t0;
		op.t0 = op.t1;
		op.t1 = op.temp;
	}
	if (op.t0 < 0)
	{
		op.t0 = op.t1;
		if (op.t0 < 0)
			return (false);
	}
	set_hit(ray, sphere, hit, &op);
	return (true);
}
