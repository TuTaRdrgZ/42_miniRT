/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 18:08:13 by bautrodr          #+#    #+#             */
/*   Updated: 2024/06/12 18:59:13 by tuta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_ssaa
{
	int				i;
	int				j;
	int				k;
	int				l;
}					t_ssaa;

typedef struct s_vector
{
	double			x;
	double			y;
	double			z;
}					t_vec;

typedef t_vec		t_point;

typedef struct s_cap
{
	t_vec			coordinates;
	t_vec			direction;
	double			radius;
}					t_cap;

typedef struct s_rgb
{
	double			r;
	double			g;
	double			b;
}					t_rgb;

typedef struct s_ray
{
	t_point			origin;
	t_vec			direction;
	int				f_first;
	double			scalar;
	t_vec			normal;
}					t_ray;

typedef struct s_operation
{
	float			a;
	float			b;
	float			c;
	float			t0;
	float			t1;
	float			temp;
}					t_op;

typedef struct s_hit
{
	t_rgb			rgb;
	t_vec			hit_point;
	t_vec			normal;
	t_ray			ray;
	double			t;
	int				did_it_hit;
}					t_hit;

typedef struct s_ambient
{
	int				total;
	double			ratio;
	t_rgb			rgb;
}					t_ambient;

typedef struct s_light
{
	int				total;
	double			ratio;
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

#endif
