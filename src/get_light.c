#include "miniRT.h"
#include "parser.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_light(t_intersec *intersec, t_light light, int *intensity)
{
	t_vec	light_direction;
	float	cos_angle;
	float	dot_product;

	light_direction = subtract_vec(light.coordinates, intersec->point);
	intersec->light = normalize_vec(light_direction);
	dot_product = dot_prod(intersec->normal, light_direction);
	cos_angle = dot_product / (length_vec(intersec->normal) * length_vec(light_direction));

	if (cos_angle < 0)
	{
		intersect->color.r = intersec->color.r * (cos_angle * -1) * light.ratio * (light.rgb.r / 255);
		intersect->color.g = intersec->color.g * (cos_angle * -1) * light.ratio * (light.rgb.g / 255);
		intersect->color.b = intersec->color.b * (cos_angle * -1) * light.ratio * (light.rgb.b / 255);
		*intensity = light.ratio;
	}
}
