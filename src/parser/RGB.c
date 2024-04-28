#include "parser.h"

int check_rgb(char *str)
{
    char **rgb;
    int rgb_colors[3];
    int i;
    int j;

    rgb = ft_split(str, ',');
    if (!rgb)
        return (printf("Malloc failed\n"), KO);
    if (arg_counter(rgb) != 3)
        return (print_matrix_error(rgb, -1), ft_free(rgb), KO);
    i = -1;
    j = -1;
    while (rgb[++i])
    {
        j = -1;
        while (rgb[i][++j])
            if (!ft_isdigit(rgb[i][j]))
                return (printf(RED"Error\nInvalid RGB: "RST), ft_free(rgb), KO);
    }
    rgb_colors[0] = ft_atoi(rgb[0]);
    rgb_colors[1] = ft_atoi(rgb[1]);
    rgb_colors[2] = ft_atoi(rgb[2]);
    if (rgb_colors[0] > 255 || rgb_colors[0] < 0 || rgb_colors[1] > 255
            || rgb_colors[1] < 0 || rgb_colors[2] > 255 || rgb_colors[2] < 0)
        return (printf(RED"Error\nInvalid RGB: "RST), ft_free(rgb), KO);
    return (ft_free(rgb), OK);
}
