#include "miniRT.h"

bool    hit_any_object(t_obj **obj, t_ray *ray)
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
                retr = true;
       }
       tmp = tmp->next;
   }
   return (retr);
}
