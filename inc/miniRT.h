#ifndef MINIRT_H
#define MINIRT_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "../lib/vector/vector.h"
#define WIDTH 1920
#define HEIGHT 1080

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
