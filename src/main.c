#include "../inc/miniRT.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// static mlx_image_t* image;

// -----------------------------------------------------------------------------

int32_t ft_pixel(t_color *color)
{
	int a = 240;

    return ((int)color->x << 24 | (int)color->y << 16 | (int)color->z << 8 | a);
}

// int	vector_to_color(t_vec color)
// {
// 	return (ft_pixel(color.x * 255, color.y * 255, color.z * 255, 255));
// }

t_vec ray_color(t_ray *ray)
{	
	if (ray->f_first == 0)
	{
		t_vec tmp = normalize_vec(ray->direction);
		ray->scalar = tmp.x / ray->direction.x;
		ray->f_first = 1;
	}
	// print_vec(ray->normalize_vec, "unit_direction");
	// printf("length: %d\n", length_vec(unit_direction));
	double a = (ray->direction.y * ray->scalar + 0.5);
	// printf("a = %f\n", a);
    return (add_vec(mult_vec_by_scal(new_vec(0, 0, 0), (1 - a)), mult_vec_by_scal(new_vec(255, 255, 255), a)));
}

// t_vec	color_clamp(t_vec color)
// {
// 	if (color.x > 1)
// 		color.x = 1;
// 	else if (color.x < 0)
// 		color.x = 0;
// 	if (color.y > 1)
// 		color.y = 1;
// 	else if (color.y < 0)
// 		color.y = 0;
// 	if (color.z > 1)
// 		color.z = 1;
// 	else if (color.z < 0)
// 		color.z = 0;
// 	return (color);
// }

// void	put_pixel(mlx_image_t *img, int x, int y, t_vec color)
// {
//     double r = color.x;
//     double g = color.y;
//     double b = color.z;

//     int ir = (int) (255.999 * r);
//     int ig = (int) (255.999 * g);
//     int ib = (int) (255.999 * b);
// 	color = color_clamp(color);
// 	if (img == NULL)
// 		return ;
//     int color_int = vector_to_color(color);
// 	mlx_put_pixel(img, x, y, color_int);
// }

void ft_color(void* param)
{
	t_data *data = (t_data*)param;
	mlx_t* mlx = data->mlx;
    mlx_image_t* image = data->image;

	for (uint32_t j = 0; j < HEIGHT; j++) {
        for (uint32_t i = 0; i < WIDTH; i++) {
            t_vec pixel_center = add_vec(data->vp->pixel00, add_vec(mult_vec_by_scal(data->vp->pixel_delta_u, i), mult_vec_by_scal(data->vp->pixel_delta_v, j)));
            t_vec ray_direction = subtract_vec(pixel_center, data->camera->origin);
            data->ray->direction = ray_direction;
			data->ray->origin = data->camera->origin;
			// print_vec(data->ray->direction, "direction");
			// print_vec(data->ray->origin, "origin");
			// print_vec(pixel_center, "pixel_center");
			*data->color = ray_color(data->ray);
			uint32_t color = ft_pixel(data->color);
			mlx_put_pixel(image, i, j, color);
        }
    }
	//data->ray->f_first = 0;
}

// -----------------------------------------------------------------------------

void ft_hook(void* param)
{
    t_data *data = (t_data*)param;
	mlx_t* mlx = data->mlx;
    mlx_image_t* image = data->image;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
}

// -----------------------------------------------------------------------------

int32_t main(void)
{
	t_data data;
	data_init(&data, WIDTH, HEIGHT);
	camera_init(data.camera);
	viewport_init(data.vp, data.camera);
	mlx_t* mlx;
	data.mlx = mlx;
	mlx_image_t* image;
	data.image = image;
	t_vec color;
	data.color = &color;

	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(data.image = mlx_new_image(mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, data.image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	mlx_loop_hook(mlx, ft_color, &data);
	mlx_loop_hook(mlx, ft_hook, &data);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	exit(EXIT_SUCCESS);
}
