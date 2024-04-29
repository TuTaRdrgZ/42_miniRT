#include "../../inc/structures.h"
#include "../parser/parser.h"
#include "../../lib/vector/vector.h"

t_sp    *init_sphere(char **data);
t_pl    *init_plane(char **data);

void    init_obj(t_obj *obj, char **obj_data, int type)
{
    t_obj *new;

    new = ft_calloc(sizeof(t_obj), 1);
    if (!new)
        return (printf("Malloc Failed\n"), exit(1));
    new->next = NULL;
    if (type == SP)
        new->object = init_sphere(obj_data);
    else if (type == PL)
        new->object = init_plane(obj_data);
    // else if (type == CY)
    //     new->object = init_cylinder(obj_data);
    if (obj)
        (find_last(obj))->next = new;
    else
        obj = new;
}

t_sp    *init_sphere(char **data)
{
    t_sp    *new;
    char    **split;

    new = ft_calloc(sizeof(t_sp), 1);
    if (!new)
        exit (-1);
    split = ft_split(data[1], ',');
    new->coordinates = new_vec(ft_atof(split[0]), ft_atof(split[1]), ft_atof(split[2]));
    new->diameter = ft_atof(data[2]);
    ft_free(split);
    split = ft_split(data[3], ',');
    new->rgb.r = ft_atoi(split[0]);
    new->rgb.g = ft_atoi(split[1]);
    new->rgb.b = ft_atoi(split[2]);
    printf("obj->diameter = %.3f\n", new->diameter);
    print_vec(new->coordinates, "sphere->position");
    printf("obj->rgb (%d, %d, %d)\n\n", new->rgb.r, new->rgb.g, new->rgb.b);
    ft_free(split);
    return (new);
}

t_pl    *init_plane(char **data)
{
    t_pl    *new;
    char    **split;

    new = ft_calloc(sizeof(t_pl), 1);
    split = ft_split(data[1], ',');
    if (!new || !split)
        exit(-1); // crear funcion exit_error
    new->coordinates = new_vec(ft_atof(split[0]), ft_atof(split[1]), ft_atof(split[2]));
    ft_free(split);
    split = ft_split(data[2], ',');
    if (!split)
        exit (-1);
    new->normal = new_vec(ft_atof(split[0]), ft_atof(split[1]), ft_atof(split[2]));
    print_vec(new->normal, "plane->normal");
    ft_free(split);
    if (!split)
        exit (-1);
    split = ft_split(data[3], ',');
    new->rgb.r = ft_atoi(split[0]);
    new->rgb.g = ft_atoi(split[1]);
    new->rgb.b = ft_atoi(split[2]);
    print_vec(new->coordinates, "obj->coordinates");
    printf("obj->rgb (%d, %d, %d)\n\n", new->rgb.r, new->rgb.g, new->rgb.b);
    ft_free(split);
    return (new);
}
