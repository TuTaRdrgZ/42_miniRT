#include "miniRT.h"

t_rgb	get_sphere_rgb(t_sp *sphere)
{
	t_rgb	color;

	color.r = sphere->rgb.r;
	color.g = sphere->rgb.g;
	color.b = sphere->rgb.b;
	return (color);
}

t_rgb	get_plane_rgb(t_pl *plane)
{
	t_rgb	color;

	color.r = plane->rgb.r;
	color.g = plane->rgb.g;
	color.b = plane->rgb.b;
	return (color);
}
