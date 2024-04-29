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
    ft_free(split);
}
