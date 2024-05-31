#include "miniRT.h"
#include "parser.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	clip_color(t_rgb *rgb)
{
	int dividor;
	int highest;

	if (rgb->r > rgb->g)
		highest = rgb->r;
	else
		highest = rgb->g;
	if (highest < rgb->b)
		highest = rgb->b;
	if (highest > 255)
	{
		dividor = highest / 255;
		rgb->r /= dividor;
		rgb->g /= dividor;
		rgb->b /= dividor;
	}

}

t_rgb fade_to_black(t_rgb color, float fade_factor)
{
	if (fade_factor > 1)
		fade_factor = 1;
    color.r = (unsigned char)((float)color.r * fade_factor);
    color.g = (unsigned char)((float)color.g * fade_factor);
    color.b = (unsigned char)((float)color.b * fade_factor);
    return color;
}

void get_light(t_hit *hit, t_light light, int *intensity, t_data data)
{
	t_vec	light_direction;
	float	cos_angle;
	float	dot_product;

	light_direction = subtract_vec(light.coordinates, hit->hit_point);
	light_direction = normalize_vec(light_direction);
	dot_product = dot_prod(hit->normal, light_direction);
	cos_angle = dot_product / (length_vec(hit->normal) * length_vec(light_direction));
	(void)data;
	(void)intensity;
	if (cos_angle > 0 && !simple_check_hit(data.obj, hit, data.light->coordinates))
	{
		// hit->rgb.r += light.rgb.r * cos_angle * light.ratio;
		// hit->rgb.g += light.rgb.g * cos_angle * light.ratio;
		// hit->rgb.b += light.rgb.b * cos_angle * light.ratio;
		//hit->rgb.r = (hit->rgb.r / 1.5) + hit->rgb.r * (light.ratio * cos_angle * (light.rgb.r / 255));
		//hit->rgb.g = (hit->rgb.g / 1.5) + hit->rgb.g * (light.ratio * cos_angle * (light.rgb.g / 255));
		//hit->rgb.b = (hit->rgb.b / 1.5) + hit->rgb.b * (light.ratio * cos_angle * (light.rgb.b / 255));
		//clip_color(&hit->rgb);
		if (hit->rgb.r > 255)
			hit->rgb.r = 255;
		if (hit->rgb.g > 255)
			hit->rgb.g = 255;
		if (hit->rgb.b > 255)
			hit->rgb.b = 255;
		hit->rgb = fade_to_black(hit->rgb, (data.ambient->ratio + (light.ratio * cos_angle)));
		// *intensity += (int)(light.ratio * cos_angle * 255);
		// if (*intensity > 255)
		// 	*intensity = 255;
	}
	else
		hit->rgb = fade_to_black(hit->rgb, data.ambient->ratio);
}
