#include "include/MLX42/MLX42.h"
#include "miniRT.h"
#include "parser.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int calculate_pixel_color(t_rgb color)
{
	return ((int)color.r << 24 | (int)color.g << 16 | (int)color.b << 8 | 255);
}

void	render_scene(void *param)
{
	t_data		*data;
	t_vec		pixel_pos;
	t_hit		hit;
	int			j;
	int			i;

	j = -1;
	data = (t_data *)param;
	data->ray->origin = data->camera->origin;
	while (++j < data->height)
	{
		i = -1;
		while (++i < data->width)
		{
			pixel_pos = add_vec(data->vp->pixel00,
					add_vec(mult_by_scal(data->vp->pixel_delta_u, i),
					mult_by_scal(data->vp->pixel_delta_v, j)));
			data->ray->direction = subtract_vec(pixel_pos, data->camera->origin);
			hit = hit_any_object(&data->obj, data->ray);
			apply_lighting(&hit, *data->light, *data);
			mlx_put_pixel(data->image, i, j, calculate_pixel_color(hit.rgb));
		}
	}
}

void	render_scene_ssaa(void *param)
{
	t_data		*data;
	t_vec		sample_pos;
	t_hit		hit;
	int			j;
	int			i;
	int			k;
	int			l;
	float		supersampling_factor = 2.0;  // Supersampling factor
	int			num_samples = supersampling_factor * supersampling_factor;

	j = -1;
	data = (t_data *)param;
	data->ray->origin = data->camera->origin;
	while (++j < data->height)
	{
		i = -1;
		while (++i < data->width)
		{
			t_rgb total_color = {0, 0, 0};
			// Supersampling loop
			for (k = 0; k < supersampling_factor; k++)
			{
				for (l = 0; l < supersampling_factor; l++)
				{
					// Calculate sample position within the pixel
					sample_pos = add_vec(data->vp->pixel00,
						add_vec(mult_by_scal(data->vp->pixel_delta_u, i + (k + 0.5) / supersampling_factor),
								mult_by_scal(data->vp->pixel_delta_v, j + (l + 0.5) / supersampling_factor)));
					data->ray->direction = subtract_vec(sample_pos, data->camera->origin);
					hit = hit_any_object(&data->obj, data->ray);
					apply_lighting(&hit, *data->light, *data);
					total_color.r += hit.rgb.r;
					total_color.g += hit.rgb.g;
					total_color.b += hit.rgb.b;
				}
			}
			// Average the color
			total_color.r /= num_samples;
			total_color.g /= num_samples;
			total_color.b /= num_samples;
			
			mlx_put_pixel(data->image, i, j, calculate_pixel_color(total_color));
		}
	}
}

void	ft_hook(void *param)
{
	t_data		*data;
	mlx_t		*mlx;

	data = (t_data *)param;
	mlx = data->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

// -----------------------------------------------------------------------------

// void	print_obj_node(t_obj *node)
// {
// 	t_cy	*cy;

// 	if (node == NULL)
// 	{
// 		printf("Nodo NULL\n");
// 		return ;
// 	}
// 	printf("Tipo %d, ", node->type);
// 	// Imprimir el objeto según su tipo
// 	if (node->type == SP)
// 	{
// 		t_sp *sp = (t_sp *)node->object; // Convertir el objeto a t_sp
// 		printf("Esfera:\n");
// 		printf("Nodo: %p\n", node);
// 		printf("Coordenadas: (%f, %f, %f)\n", sp->coordinates.x,
// 			sp->coordinates.y, sp->coordinates.z);
// 		printf("Color RGB: (%d, %d, %d)\n", sp->rgb.r, sp->rgb.g, sp->rgb.b);
// 		printf("Diámetro: %f\n", sp->diameter);
// 	}
// 	else if (node->type == PL)
// 	{
// 		t_pl *pl = (t_pl *)node->object; // Convertir el objeto a t_pl
// 		printf("Plano:\n");
// 		printf("Nodo: %p\n", node);
// 		printf("Coordenadas: (%f, %f, %f)\n", pl->coordinates.x,
// 			pl->coordinates.y, pl->coordinates.z);
// 		printf("Normal: (%f, %f, %f)\n", pl->normal.x, pl->normal.y,
// 			pl->normal.z);
// 		printf("Color RGB: (%d, %d, %d)\n", pl->rgb.r, pl->rgb.g, pl->rgb.b);
// 	}
// 	else if (node->type == CY)
// 	{
// 		cy = (t_cy *)node->object;
// 		printf("Cilindro:\n");
// 		printf("Nodo: %p\n", node);
// 		printf("Coordenadas: (%f, %f, %f)\n", cy->coordinates.x,
// 			cy->coordinates.y, cy->coordinates.z);
// 		printf("Normal: (%f, %f, %f)\n", cy->normal.x, cy->normal.y,
// 			cy->normal.z);
// 		printf("Diámetro: %f\n", cy->diameter);
// 		printf("Altura: %f\n", cy->height);
// 		printf("Color RGB: (%d, %d, %d)\n", cy->rgb.r, cy->rgb.g, cy->rgb.b);
// 	}
// 	else
// 	{
// 		printf("Tipo de objeto desconocido: %d\n", node->type);
// 	}
// 	printf("Siguiente nodo: %p\n\n", node->next);
// }

// void	print_all_nodes(t_data *data)
// {
// 	t_obj	*obj;

// 	obj = data->obj;
// 	while (obj)
// 	{
// 		print_obj_node(obj);
// 		obj = obj->next;
// 	}
// }

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

int	free_data(t_data *data)
{
	free(data->ray);
	free(data->camera);
	free(data->vp);
	free(data->ambient);
	free(data->light);
	free_all_objects(data);
    return (1);
}

void	close_callback(void *param)
{
    if (param)
        exit(0);
    exit(0);
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
	data_init(&data);
	if (read_file(&data, file))
        return (free_data(&data));
	if (check_duplicated(&data))
        return (free_data(&data));
	viewport_init(data.vp, data.camera, data.width, data.height);
	if (!(mlx = mlx_init(data.width, data.height, "MLX42", false)))
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(mlx, data.width, data.height)))
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
	//print_all_nodes(&data);
    if (SSAA)
        render_scene_ssaa(&data);
    else
        render_scene(&data);
	mlx_loop_hook(mlx, ft_hook, &data);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	free_data(&data);
	exit(EXIT_SUCCESS);
}
