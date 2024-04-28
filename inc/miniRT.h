#ifndef MINIRT_H
#define MINIRT_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "../lib/libft/libft.h"
#include "../lib/vector/vector.h"
#define WIDTH 1920
#define HEIGHT 1080

# define RST "\033[0m"    /* Reset to default color */
# define RED "\033[1;31m" /* Bold Red */
# define G "\033[1;32m"   /* Bold Green */
# define Y "\033[1;33m"   /* Bold Yellow */
# define B "\033[1;34m"   /* Bold Blue */
# define M "\033[1;35m"   /* Bold Magenta */
# define C "\033[1;36m"   /* Bold Cyan */
# define W "\033[1;37m"   /* Bold White */

typedef struct s_ray
{
	t_vec	origin;
	t_vec	direction;
	t_vec	normal;
}			t_ray;

typedef struct s_camera
{
  // Posición de la cámara en el espacio 3D
  t_vec origin;

  // Dirección hacia la que apunta la cámara
  t_vec direction;

  // Vector hacia arriba (para definir la orientación)
  t_vec up;

  // Campo de visión horizontal (en radianes)
  float fov_h;

  // Ratio de aspecto (ancho/alto)
  float aspect_ratio;

  // Distancia focal (para el zoom)
  float focal_length;

  // Valor de apertura (para el desenfoque)
  float aperture;
}			t_camera;

typedef struct s_data {
    mlx_t *mlx;
    mlx_image_t* image;
    t_vec *color;
    t_ray *ray;
    t_camera *camera;
    int     width;
    int     height;
}            t_data;

void init_camera(t_camera *camera, t_vec origin, t_vec direction, t_vec up, float fov_h, float aspect_ratio);

#endif
