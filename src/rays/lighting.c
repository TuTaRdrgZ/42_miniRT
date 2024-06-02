#include "miniRT.h"

t_rgb fade_to_shade(t_rgb color, double fade_factor)
{
	if (fade_factor > 1)
		fade_factor = 1;
    color.r *= fade_factor;
    color.g *= fade_factor;
    color.b *= fade_factor;
    return color;
}

void apply_lighting(t_hit *hit, t_light light, t_data data)
{
	t_vec	light_direction;
	float	cos_angle;
	float	dot_product;

	light_direction = normalize_vec(subtract_vec(light.coordinates, hit->hit_point));
	dot_product = dot_prod(hit->normal, light_direction);
	cos_angle = dot_product / (length_vec(hit->normal) * length_vec(light_direction));
	if (cos_angle > 0 && !simple_check_hit(data.obj, hit, data.light->coordinates))
		hit->rgb = fade_to_shade(hit->rgb, (data.ambient->ratio + (light.ratio * cos_angle)));
	else
		hit->rgb = fade_to_shade(hit->rgb, data.ambient->ratio);
}
