#include "../inc/miniRT.h"

void viewport_init(t_vp *vp, t_camera *camera)
{
    vp->vp_height = 2.0;
    vp->vp_width = vp->vp_height * camera->aspect_ratio;
    vp->focal_length = camera->focal_length;

    vp->u = new_vec(vp->vp_width, 0, 0);
    vp->v = new_vec(0, -vp->vp_height, 0);

    vp->pixel_delta_u = div_vec_by_scal(vp->u, vp->vp_width);
    vp->pixel_delta_v = div_vec_by_scal(vp->v, vp->vp_height);

    vp->upper_left = add_vec(camera->origin, new_vec(0, vp->focal_length, 0));
    vp->upper_left = add_vec(vp->upper_left, mult_vec_by_scal(vp->u, 0.5));
    vp->upper_left = add_vec(vp->upper_left, mult_vec_by_scal(vp->v, 0.5));

    vp->pixel00 = add_vec(vp->upper_left, mult_vec_by_scal(vp->pixel_delta_u, 0.5));
    vp->pixel00 = add_vec(vp->pixel00, mult_vec_by_scal(vp->pixel_delta_v, 0.5));
}
