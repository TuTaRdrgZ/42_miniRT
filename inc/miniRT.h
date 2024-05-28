#ifndef MINIRT_H
#define MINIRT_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "../lib/libft/libft.h"
#include "vector.h"
#include "structures.h"
// #include "../src/parser/parser.h"
#define WIDTH 900
#define HEIGHT 440
#define SP 0
#define PL 1
#define CY 2

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
  // Punto de origen del rayo
	t_point	origin;

	// Dirección del rayo
	t_vec	direction;

	int f_first;
	double scalar;
	t_vec	normal;
}			t_ray;

typedef struct s_camera
{
    int    total;
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
    t_ray *ray;
    t_camera *camera;
    t_vp *vp;
    t_obj   *obj;
    t_ambient *ambient;
    t_light     *light;
    int     width;
    int     height;
}            t_data;

void camera_init(t_camera *camera, char **data);
void data_init(t_data *data, int width, int height);
t_point new_point(float x, float y, float z);
void viewport_init(t_vp *vp, t_camera *camera);

int32_t ft_pixel(t_rgb color);
t_intersec	hit_any_object(t_obj **obj, t_ray *ray);
bool 	hit_sphere(t_ray *ray, t_sp *sphere, t_vec *hit_point, t_vec *normal);
bool	hit_plane(const t_ray *ray, const t_pl *plane, t_vec *hit_point, t_vec *normal);

void    init_light(t_light *light, char **data);
void    init_ambient(t_ambient *ambient, char **data);
void    init_obj(t_obj **obj, char **obj_data, int type);
t_sp    *init_sphere(char **data);
t_pl    *init_plane(char **data);
#endif
