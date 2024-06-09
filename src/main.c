/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 19:35:06 by bautrodr          #+#    #+#             */
/*   Updated: 2024/06/09 20:54:15 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "parser.h"
#include <time.h>

int	calculate_pixel_color(t_rgb color)
{
	return ((int)color.r << 24 | (int)color.g << 16 | (int)color.b << 8 | 255);
}

void	render_scene(void *param)
{
	t_data	*data;
	t_vec	pixel_pos;
	t_hit	hit;
	int		j;
	int		i;

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
			data->ray->direction = subtract_vec(pixel_pos,
					data->camera->origin);
			hit = hit_any_object(&data->obj, data->ray);
			apply_lighting(&hit, *data->light, *data);
			mlx_put_pixel(data->image, i, j, calculate_pixel_color(hit.rgb));
		}
	}
}

void	ft_hook(void *param)
{
	t_data	*data;
	mlx_t	*mlx;

	data = (t_data *)param;
	mlx = data->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

int	init_mlx(t_data *data)
{
	mlx_t		*mlx;
	mlx_image_t	*image;

	mlx = mlx_init(data->width, data->height, "MLX42", false);
	if (!mlx)
	{
		printf("%s\n", mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	image = mlx_new_image(mlx, data->width, data->height);
	if (!image || mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		printf("%s\n", mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	data->mlx = mlx;
	data->image = image;
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (print_error("Invalid arguments\n"));
	if (!is_valid_filetype(argv[1]))
		return (printf("Wrong filetype\n"), 1);
	data_init(&data);
	if (read_file(&data, argv[1]) || check_duplicated(&data))
		return (free_data(&data));
	viewport_init(data.vp, data.camera, data.width, data.height);
	if (init_mlx(&data))
		return (EXIT_FAILURE);
	if (data.ssaa)
		render_scene_ssaa(&data);
	else
		render_scene(&data);
	mlx_loop_hook(data.mlx, ft_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	free_data(&data);
	return (0);
}
