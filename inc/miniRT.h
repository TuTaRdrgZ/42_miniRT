#ifndef MINIRT_H
#define MINIRT_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "../lib/libft/libft.h"
#include "structures.h"
// #include "../src/parser/parser.h"
#define WIDTH 1920
#define HEIGHT 1080
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

typedef struct s_camera
{
  int    total;
  t_point origin;
  t_vec   direction;
  float   aspect_ratio;
  double   focal_length;

}			t_camera;

typedef struct viewport
{
  double vp_width;
  double vp_height;
  double vp_distance;
  t_vec u;
  t_vec v;
  t_vec pixel_delta_u;
  t_vec pixel_delta_v;
  t_point upper_left;
  t_vec pixel00;
}			t_vp;

typedef struct s_data
{
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

void    camera_init(t_camera *camera, char **data);
void    data_init(t_data *data, int width, int height);
t_point new_point(float x, float y, float z);
void    viewport_init(t_vp *vp, t_camera *camera);
void    apply_lighting(t_hit *hit, t_light light, t_data data);
t_rgb   new_rgb(double r, double g, double b);

int     calculate_pixel_color(t_rgb color);
t_hit   hit_any_object(t_obj **obj, t_ray *ray);
bool    hit_sphere(t_ray *ray, t_sp *sphere, t_vec *hit_point, t_vec *normal);
bool    hit_plane(const t_ray *ray, const t_pl *plane, t_vec *hit_point, t_vec *normal);
bool    hit_cylinder(t_ray *ray, t_cy *cylinder, t_vec *hit_point, t_vec *normal);
bool    simple_check_hit(t_obj *obj, t_hit *hit, t_vec light);
bool    solve_quadratic(t_op *op);

t_rgb   get_plane_rgb(t_pl *plane);
t_rgb   get_sphere_rgb(t_sp *sphere);
t_rgb   get_cylinder_rgb(t_cy *cylinder);

/********** STRUCT INITIALIZATION **********/
void    init_light(t_light *light, char **data);
void    init_ambient(t_ambient *ambient, char **data);
void    init_obj(t_obj **obj, char **obj_data, int type);
t_sp    *init_sphere(char **data);
t_pl    *init_plane(char **data);

/********** VECTORS **********/
t_vec   add_vec(t_vec a, t_vec b);
t_vec   subtract_vec(t_vec a, t_vec b);
t_vec   mult_by_scal(t_vec a, double scalar);
t_vec   div_by_scal(t_vec a, double scalar);
t_vec   cross_prod(t_vec a, t_vec b);
t_vec   normalize_vec(t_vec a);
t_vec   new_vec(double x, double y, double z);
float   distance_vec(t_vec a, t_vec b);
double  dot_prod(t_vec a, t_vec b);
double  length_vec(t_vec a);

#endif
