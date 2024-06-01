#include "miniRT.h"
#include "parser.h"

t_point	new_point(float x, float y, float z)
{
	t_point	point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

t_vec	*new_v(int x, int y, int z)
{
	t_vec	*tmp;

	tmp = malloc(sizeof(t_vec));
	tmp->x = x;
	tmp->y = y;
	tmp->z = z;
	return (tmp);
}

void	camera_init(t_camera *camera, char **data)
{
	char	**split;

	split = ft_split(data[1], ',');
	if (!split)
		exit(EXIT_FAILURE);
	camera->origin = new_point(ft_atof(split[0]), ft_atof(split[1]),
			ft_atof(split[2]));
	ft_free(split);
	split = ft_split(data[2], ',');
	camera->direction = new_vec(ft_atof(split[0]), ft_atof(split[1]),
			ft_atof(split[2]));
	ft_free(split);
	camera->focal_length = 5.1 - (((double)ft_atoi(data[3])) / 36.0);
	camera->aspect_ratio = 16.0 / 9.0;
	camera->total++;
}

void	data_init(t_data *data, int width, int height)
{
	data->width = width;
	data->height = height;
	data->ray = malloc(sizeof(t_ray));
	if (!data->ray)
		exit(EXIT_FAILURE);
	data->ray->f_first = 0;
	data->camera = ft_calloc(sizeof(t_camera), 1);
	if (!data->camera)
		exit(EXIT_FAILURE);
	data->vp = malloc(sizeof(t_vp));
	if (!data->vp)
		exit(EXIT_FAILURE);
	data->ambient = ft_calloc(sizeof(t_ambient), 1);
	if (!data->ambient)
		exit(EXIT_FAILURE);
	data->light = ft_calloc(sizeof(t_light), 1);
	if (!data->light)
		exit(EXIT_FAILURE);
	data->obj = NULL;
}

void	viewport_init(t_vp *vp, t_camera *camera)
{
	vp->vp_height = 2;
	vp->vp_width = vp->vp_height * camera->aspect_ratio;
	vp->focal_length = camera->focal_length;
	vp->u = cross_prod(camera->direction, add_vec(camera->direction, new_vec(0, 1, 0)));
	vp->v = cross_prod(camera->direction, vp->u);
	vp->u = normalize_vec(vp->u);
	vp->v = normalize_vec(vp->v);
	vp->u = mult_vec_by_scal(vp->u, vp->vp_width);
	vp->v = mult_vec_by_scal(vp->v, vp->vp_height);
	vp->pixel_delta_u = div_vec_by_scal(vp->u, WIDTH);
	vp->pixel_delta_v = div_vec_by_scal(vp->v, HEIGHT);
	vp->upper_left = add_vec(camera->origin, mult_vec_by_scal(camera->direction, (double)vp->focal_length));
	vp->upper_left = add_vec(vp->upper_left, mult_vec_by_scal(vp->u, -0.5));
	vp->upper_left = add_vec(vp->upper_left, mult_vec_by_scal(vp->v, -0.5));
	vp->pixel00 = add_vec(vp->upper_left, mult_vec_by_scal(vp->pixel_delta_u,
				0.5));
	vp->pixel00 = add_vec(vp->pixel00, mult_vec_by_scal(vp->pixel_delta_v,
				0.5));
}
