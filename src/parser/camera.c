#include "parser.h"

int check_normalized_vector(char *str)
{
    char **nor_matrix;
    int i;
    float number;

    nor_matrix = ft_split(str, ',');
    if (!nor_matrix)
        exit(-1);
    i = -1;
    if (arg_counter(nor_matrix) != 3)
        return (printf(RED"Error\nInvalid orientation vector: %s\n"RST, str), ft_free(nor_matrix), KO);
    while (nor_matrix[++i])
    {
        if (check_negative(nor_matrix[i]))
            return (ft_free(nor_matrix), KO);
        if (check_dot(nor_matrix[i], -1, 0, -1))
            return (ft_free(nor_matrix), KO);
        number = ft_atof(nor_matrix[i]);
        if (number > 1 || number < -1)
            return (printf(RED"Error\nInvalid orientation vector: %s\n"RST, str), ft_free(nor_matrix), KO);
    }
    return (ft_free(nor_matrix), OK);
}

int check_fov(char *fov)
{
    if (ft_atoi(fov) < 0 || ft_atoi(fov) > 180)
        return (printf(RED"Error\nInvalid FOV [0,180]: %s\n", fov), KO);
    return (OK);
}

int check_camera(char **camera, int argc)
{
    if (argc != 4)
        return (print_error("Error\nInvalid camera arguments\n"), KO);
    if (check_coordinates(camera[1]))
        return (KO);
    if (check_normalized_vector(camera[2]))
        return (KO);
    if (check_fov(camera[3]))
        return (KO);
    return (OK);
}
