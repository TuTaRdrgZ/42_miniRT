#include "parser.h"

int check_sphere(char **matrix, int argc);

int check_obj(char **matrix, int argc, int type)
{
    if ((argc != 4 && (type == SP || type == PL)) || (type == CY && argc != 6))
        return (print_error("Wrong N of obj arguments\n"));
    if (type == SP)
        if (check_sphere(matrix, argc))
            return (KO);
    return (OK);
}

int check_sphere(char **matrix, int argc)
{
    if (check_coordinates(matrix[1]))
        return (KO);
    if (check_diameter(matrix[2]) == KO)
        return (KO);
    return (OK);
}
