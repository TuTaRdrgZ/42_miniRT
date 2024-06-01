#ifndef STRUCTURES_H
# define STRUCTURES_H
# include "../lib/vector/vector.h"

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

typedef struct s_operation
{
	float			a;
	float			b;
	float			c;
	float			t0;
	float			t1;
	float			temp;
}					t_op;

typedef struct s_rgb
{
	double			r;
	double			g;
	double			b;
}					t_rgb;

typedef struct		s_hit
{
	t_rgb	rgb;
	t_vec	hit_point;
	t_vec	normal;
    t_ray   ray;
	int		didItHit;
}					t_hit;

typedef struct s_ambient
{
	int total; // for checking if there are more than 1 ambient light
	double			ratio;
	t_rgb			rgb;
}					t_ambient;

typedef struct s_light
{
	int total; // currently not needed
	double			ratio;
	t_rgb			rgb;
	t_vec			coordinates;
}					t_light;

typedef struct s_obj
{
	int				type;
	void			*object;
	struct s_obj	*next;
}					t_obj;  

typedef struct s_sp
{
	t_vec			coordinates; 
	t_rgb			rgb;
	float			diameter;
	float			radius;
}					t_sp;

typedef struct s_pl
{
	t_vec			coordinates;
	t_vec			normal;
	t_rgb			rgb;
}					t_pl;

typedef struct s_cy
{
	t_vec			coordinates;
	t_vec			normal;
	float			diameter;
	float			height;
	t_rgb			rgb;
}					t_cy;

t_obj				*find_last(t_obj **obj);
#endif
