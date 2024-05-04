#include "miniRT.h"
#include <lib/vector/vector.h>

bool    hit_any_object(t_obj **obj, t_ray *ray, int i, int j, t_data *data)
{
   t_obj *tmp;
   bool retr;
   
   retr = false;
   tmp = *obj;
   while (tmp)
   {
       if (tmp->type == SP)
       {
           if (hit_sphere(ray, tmp->object))
           {
               retr = true;
               t_sp *sphere = tmp->object;
               int color = ft_pixel(sphere->rgb);
               mlx_put_pixel(data->image, i, j, color);
           }
       }
       if (tmp->type == PL)
       {
           if (hit_plane(ray, (t_pl*)tmp->object))
           {
               t_pl *plane = tmp->object;
               int color = ft_pixel(plane->rgb);
               mlx_put_pixel(data->image, i, j, color);
               retr = true;
           }
       }
       tmp = tmp->next;
   }
   return (retr);
}

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

