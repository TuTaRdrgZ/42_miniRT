#include "miniRT.h"
#include "parser.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// static mlx_image_t* image;

// -----------------------------------------------------------------------------

int32_t	ft_pixel(t_rgb color)
{
	return ((int)color.r << 24 | (int)color.g << 16 | (int)color.b << 8 | 255);
}

// int	vector_to_color(t_vec color)
// {
// 	return (ft_pixel(color.x * 255, color.y * 255, color.z * 255, 255));
// }

t_vec	ray_color(t_ray *ray)
{
	t_vec	tmp;
	double	a;

	if (ray->f_first == 0)
	{
		tmp = normalize_vec(ray->direction);
		ray->scalar = tmp.x / ray->direction.x;
		ray->f_first = 1;
	}
	// print_vec(ray->normalize_vec, "unit_direction");
	// printf("length: %d\n", length_vec(unit_direction));
	a = (ray->direction.y * ray->scalar + 0.5);
	// printf("a = %f\n", a);
	return (add_vec(mult_vec_by_scal(new_vec(0, 0, 0), (1 - a)),
			mult_vec_by_scal(new_vec(255, 255, 255), a)));
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

void	ft_color(void *param)
{
	t_data		*data;
	mlx_image_t	*image;
	uint32_t	color;
	t_vec		pixel_center;
	t_vec		ray_direction;

	data = (t_data *)param;
	image = data->image;
	for (uint32_t j = 0; j < HEIGHT; j++)
	{
		for (uint32_t i = 0; i < WIDTH; i++)
		{
			color = 255;
			pixel_center = add_vec(data->vp->pixel00,
					add_vec(mult_vec_by_scal(data->vp->pixel_delta_u, i),
						mult_vec_by_scal(data->vp->pixel_delta_v, j)));
			ray_direction = subtract_vec(pixel_center, data->camera->origin);
			data->ray->direction = ray_direction;
			data->ray->origin = data->camera->origin;
			if (hit_any_object(&data->obj, data->ray, i, j, data))
				continue ;
			color = 0;
			mlx_put_pixel(image, i, j, color);
		}
	}
	// data->ray->f_first = 0;
}

// -----------------------------------------------------------------------------

void	ft_hook(void *param)
{
	t_data		*data;
	mlx_t		*mlx;
	mlx_image_t	*image;

	data = (t_data *)param;
	mlx = data->mlx;
	image = data->image;
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

void	print_obj_node(t_obj *node)
{
	t_cy	*cy;

	if (node == NULL)
	{
		printf("Nodo NULL\n");
		return ;
	}
	printf("Tipo %d, ", node->type);
	// Imprimir el objeto según su tipo
	if (node->type == SP)
	{
		t_sp *sp = (t_sp *)node->object; // Convertir el objeto a t_sp
		printf("Esfera:\n");
		printf("Nodo: %p\n", node);
		printf("Coordenadas: (%f, %f, %f)\n", sp->coordinates.x,
			sp->coordinates.y, sp->coordinates.z);
		printf("Color RGB: (%d, %d, %d)\n", sp->rgb.r, sp->rgb.g, sp->rgb.b);
		printf("Diámetro: %f\n", sp->diameter);
	}
	else if (node->type == PL)
	{
		t_pl *pl = (t_pl *)node->object; // Convertir el objeto a t_pl
		printf("Plano:\n");
		printf("Nodo: %p\n", node);
		printf("Coordenadas: (%f, %f, %f)\n", pl->coordinates.x,
			pl->coordinates.y, pl->coordinates.z);
		printf("Normal: (%f, %f, %f)\n", pl->normal.x, pl->normal.y,
			pl->normal.z);
		printf("Color RGB: (%d, %d, %d)\n", pl->rgb.r, pl->rgb.g, pl->rgb.b);
	}
	else if (node->type == CY)
	{
		cy = (t_cy *)node->object;
		printf("Cilindro:\n");
		printf("Nodo: %p\n", node);
		printf("Coordenadas: (%f, %f, %f)\n", cy->coordinates.x,
			cy->coordinates.y, cy->coordinates.z);
		printf("Normal: (%f, %f, %f)\n", cy->normal.x, cy->normal.y,
			cy->normal.z);
		printf("Diámetro: %f\n", cy->diameter);
		printf("Altura: %f\n", cy->height);
		printf("Color RGB: (%d, %d, %d)\n", cy->rgb.r, cy->rgb.g, cy->rgb.b);
	}
	else
	{
		printf("Tipo de objeto desconocido: %d\n", node->type);
	}
	printf("Siguiente nodo: %p\n\n", node->next);
}

void	print_all_nodes(t_data *data)
{
	t_obj	*obj;

	obj = data->obj;
	while (obj)
	{
		print_obj_node(obj);
		obj = obj->next;
	}
}

void	free_all_objects(t_data *data)
{
	t_obj	*obj;
	t_obj	*tmp;

	obj = data->obj;
	while (obj)
	{
		tmp = obj->next;
		if (obj->object)
			free(obj->object);
		free(obj);
		obj = tmp;
	}
}

void	free_data(t_data *data)
{
	free(data->ray);
	free(data->camera);
	free(data->vp);
	free(data->ambient);
	free(data->light);
	free_all_objects(data);
}

int32_t	main(int argc, char **argv)
{
	t_data		data;
	char		*file;
	mlx_t		*mlx;
	mlx_image_t	*image;

	if (argc != 2)
		return (print_error("Invalid arguments\n"));
	file = argv[1];
	if (!is_valid_filetype(file))
		return (printf("Wrong filetype\n"), 1);
	data_init(&data, WIDTH, HEIGHT);
	if (read_file(&data, file))
		return (1);
	if (check_duplicated(&data))
		return (1);
	viewport_init(data.vp, data.camera);
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false)))
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	data.mlx = mlx;
	data.image = image;
	print_all_nodes(&data);
	mlx_loop_hook(mlx, ft_color, &data);
	mlx_loop_hook(mlx, ft_hook, &data);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	free_data(&data);
	exit(EXIT_SUCCESS);
}
