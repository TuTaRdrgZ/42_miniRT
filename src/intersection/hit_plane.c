#include "libft/libft.h"
#include "vector/vector.h"
#include <miniRT.h>

bool hit_plane(const t_ray *ray, const t_pl *plane)
{
	float	dn;
	float	xv;
	float	t;

	dn = dot_prod(ray->direction, plane->normal);
	xv = dot_prod(subtract_vec(plane->coordinates, ray->origin), plane->normal);
	if (!dn || (dn > 0 && xv > 0) || (dn > 0 && xv > 0))
		return (false);
	t = -xv / dn;
	if (t <= 0.0001)
		return (false);
	return (true);
}
