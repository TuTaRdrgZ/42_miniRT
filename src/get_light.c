#include "miniRT.h"
#include "parser.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_light(t_hit *hit, t_light light, int *intensity)
{
	t_vec	light_direction;
	float	cos_angle;
	float	dot_product;

	light_direction = subtract_vec(light.coordinates, hit->hit_point);
	light_direction = normalize_vec(light_direction);
	dot_product = dot_prod(hit->normal, light_direction);
	cos_angle = dot_product / (length_vec(hit->normal) * length_vec(light_direction));
	if (cos_angle > 0)
	{
		hit->rgb.r += light.rgb.r * cos_angle * light.ratio;
		hit->rgb.g += light.rgb.g * cos_angle * light.ratio;
		hit->rgb.b += light.rgb.b * cos_angle * light.ratio;
		if (hit->rgb.r > 255)
			hit->rgb.r = 255;
		if (hit->rgb.g > 255)
			hit->rgb.g = 255;
		if (hit->rgb.b > 255)
			hit->rgb.b = 255;
		*intensity += (int)(light.ratio * cos_angle * 255);
		if (*intensity > 255)
			*intensity = 255;
	}
}
