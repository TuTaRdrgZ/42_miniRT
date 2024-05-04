#include "miniRT.h"
#include <lib/vector/vector.h>

bool    hit_any_object(t_obj **obj, t_ray *ray)
{
   t_obj *tmp;
   bool retr;
   
   retr = false;
   tmp = *obj;
   float t = 0.0;
   while (tmp)
   {
       if (tmp->type == SP)
       {
            if (hit_sphere(ray, tmp->object))
                retr = true;
       }
       if (tmp->type == PL)
       {
           if (intersect_plane(ray, (t_pl*)tmp->object, &t))
               retr = true;
       }
       tmp = tmp->next;
   }
   return (retr);
}

bool intersect_plane(const t_ray *ray, const t_pl *plane, float *t)
{
  // Calculate normal vector dot product with ray direction
  float denom = dot_prod(plane->normal, ray->direction);

  // Check for parallel ray and plane (denom close to zero)
  if (fabs(denom) < 1e-6f) {
    return false;
  }

  // Calculate distance from plane origin to ray origin
  float d = dot_prod(subtract_vec(plane->coordinates, ray->origin), plane->normal);

  // Calculate intersection parameter (t)
  *t = d / denom;

  // Check if intersection happens in front of the ray (positive t)
  return *t > 0.0f;
}
