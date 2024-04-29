#ifndef STRUCTURES_H
#define STRUCTURES_H
#include "../lib/vector/vector.h"

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}						t_rgb;

typedef struct  s_ambient
{
    double  ratio;
    t_rgb   rgb;
}           t_ambient;

typedef struct s_obj
{
    int          type;
    void         *object;
    struct s_obj *next;
}              t_obj;

typedef struct s_sp
{
	t_vec		coordinates;
	t_rgb		rgb;
	float		diameter;
}							t_sp;

typedef struct s_pl
{
    t_vec       coordinates;
    t_vec       normal;
    t_rgb       rgb;
}               t_pl;

t_obj	*find_last(t_obj *obj);
#endif
