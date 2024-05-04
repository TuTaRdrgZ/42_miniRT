#include "../../inc/structures.h"
#include "../parser/parser.h"

void init_ambient(t_ambient *ambient, char **data)
{
    char    **split;

    split = ft_split(data[2], ',');
    if (!split)
        exit(EXIT_FAILURE);
    ambient->ratio = ft_atof(data[1]);
    ambient->rgb.r = ft_atoi(split[0]);
    ambient->rgb.g = ft_atoi(split[1]);
    ambient->rgb.b = ft_atoi(split[2]);
    ambient->total++;
    ft_free(split);
}

void    init_light(t_light *light, char **data)
{
    char **split;
     
    split = ft_split(data[1], ',');
    if (!split)
        exit(EXIT_FAILURE);
    light->coordinates = new_vec(ft_atof(split[0]),
            ft_atof(split[1]), ft_atof(split[2]));
    ft_free(split);
    light->ratio = ft_atof(data[2]);
    split = ft_split(data[3], ',');
    light->rgb.r = ft_atoi(split[0]);
    light->rgb.g = ft_atoi(split[1]);
    light->rgb.b = ft_atoi(split[2]);
    light->total++;
    ft_free(split);
}
