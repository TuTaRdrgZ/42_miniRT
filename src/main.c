#include "../inc/miniRT.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// -----------------------------------------------------------------------------

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

int	vector_to_color(t_vec color)
{
	return (ft_pixel(color.x * 255, color.y * 255, color.z * 255, 255));
}

t_vec ray_color(t_vec ray)
{
    return (new_vector(0, 0, 0));
}

t_vec	color_clamp(t_vec color)
{
	if (color.x > 1)
		color.x = 1;
	else if (color.x < 0)
		color.x = 0;
	if (color.y > 1)
		color.y = 1;
	else if (color.y < 0)
		color.y = 0;
	if (color.z > 1)
		color.z = 1;
	else if (color.z < 0)
		color.z = 0;
	return (color);
}

void	put_pixel(mlx_image_t *img, int x, int y, t_vec color)
{
    double r = color.x;
    double g = color.y;
    double b = color.z;

    int ir = (int) (255.999 * r);
    int ig = (int) (255.999 * g);
    int ib = (int) (255.999 * b);
	color = color_clamp(color);
	if (img == NULL)
		return ;
    int color_int = vector_to_color(color);
	mlx_put_pixel(img, x, y, color_int);
}

void ft_color(void* param)
{
    t_data *data = (t_data*)param;
    double r;
    double g;
    double b;

    for (int j = 0; j < HEIGHT; j++)
    {
        for (int i = 0; i < WIDTH; i++)
        {
            // Compute the ray color
            r = (double)i / (WIDTH - 1);
            g = (double)j / (HEIGHT - 1);
            b = 0;
            put_pixel(data->image, i, j, (t_vec){r, g, b});
        }
    }
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
	mlx_t* mlx;
    t_data *data;
    mlx_image_t* image;

	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
    memset(data, 0, sizeof(t_data));
    data->mlx = mlx;
	if (!(image = mlx_new_image(mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
    data->image = image;
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	mlx_loop_hook(mlx, ft_color, data);
	mlx_loop_hook(mlx, ft_hook, data);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
