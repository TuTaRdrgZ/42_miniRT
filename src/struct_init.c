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
	camera->up = new_vec(0, 1, 0);
	camera->fov_h = ft_atoi(data[3]);
	camera->aspect_ratio = 16.0 / 9.0;
	camera->focal_length = 2.0;
	camera->aperture = 0.0;
	camera->total++;
}

void	data_init(t_data *data, int width, int height)
{
	data->width = width;
	data->height = height;
	data->ray = malloc(sizeof(t_ray));
	data->ray->f_first = 0;
	data->camera = ft_calloc(sizeof(t_camera), 1);
	data->vp = malloc(sizeof(t_vp));
	data->ambient = ft_calloc(sizeof(t_ambient), 1);
	data->light = ft_calloc(sizeof(t_light), 1);
	data->obj = NULL;
}

void	viewport_init(t_vp *vp, t_camera *camera)
{
	vp->vp_height = 2;
	vp->vp_width = vp->vp_height * camera->aspect_ratio;
	vp->focal_length = camera->focal_length;
	vp->u = new_vec(vp->vp_width, 0, 0);
	vp->v = new_vec(0, -vp->vp_height, 0);
	// printf("height: %.4f\n", vp->vp_height);
	// printf("width: %.4f\n", vp->vp_width);
	// print_vec(vp->v, "v");
	// print_vec(vp->u, "u");
	vp->pixel_delta_u = div_vec_by_scal(vp->u, WIDTH);
	vp->pixel_delta_v = div_vec_by_scal(vp->v, HEIGHT);
	vp->upper_left = add_vec(camera->origin, new_vec(0, 0, -vp->focal_length));
	vp->upper_left = add_vec(vp->upper_left, mult_vec_by_scal(vp->u, -0.5));
	vp->upper_left = add_vec(vp->upper_left, mult_vec_by_scal(vp->v, -0.5));
	vp->pixel00 = add_vec(vp->upper_left, mult_vec_by_scal(vp->pixel_delta_u,
				0.5));
	vp->pixel00 = add_vec(vp->pixel00, mult_vec_by_scal(vp->pixel_delta_v,
				0.5));
	// print_vec(vp->pixel_delta_u, "pixel_delta_u");
	// print_vec(vp->pixel_delta_v, "pixel_delta_v");
	// print_vec(vp->upper_left, "upper_left");
	// print_vec(vp->pixel00, "pixel00");
}
