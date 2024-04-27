#ifndef MINIRT_H
#define MINIRT_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "../lib/vector/vector.h"
#define WIDTH 400
#define HEIGHT 225

typedef struct s_ray
{
  // Punto de origen del rayo
	t_point	origin;

  // Dirección del rayo
	t_vec	direction;

  int f_first;
  double scalar;


  // Vector normal a la superficie impactada
	t_vec	normal;
}			t_ray;

typedef struct s_camera
{
  // Posición de la cámara en el espacio 3D
  t_point origin;

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

typedef struct viewport
{
  double vp_width;
  double vp_height;

  // Distance between the camera and the vp
  float focal_length;

  t_vec u;
  t_vec v;

  t_vec pixel_delta_u;
  t_vec pixel_delta_v;

  t_point upper_left;
  t_vec pixel00;
}			t_vp;

typedef struct s_data {
    mlx_t *mlx;
    mlx_image_t* image;
    t_vec *color;
    t_ray *ray;
    t_camera *camera;
    t_vp *vp;
    int     width;
    int     height;
}            t_data;

// void init_camera(t_camera *camera, t_vec origin, t_vec direction, t_vec up, float fov_h, float aspect_ratio);
void camera_init(t_camera *camera);
void data_init(t_data *data, int width, int height);
t_point new_point(float x, float y, float z);
void viewport_init(t_vp *vp, t_camera *camera);

#endif
