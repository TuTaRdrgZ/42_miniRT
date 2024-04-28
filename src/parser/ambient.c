#include "parser.h"

int check_dot(char *str)
{
    char    **dotarg;
    int i;
    int j;

    i = -1;
    j = -1;
    dotarg = ft_split(str, '.');
    while (dotarg[++i])
    {
        j = -1;
        while (dotarg[i][++j])
        {
            if (!ft_isdigit(dotarg[i][j]))
                 return (printf(RED "Invalid char: %c\n" RST, dotarg[i][j]));
        }
    }
    if (ft_strlen(str) < 3 || str[0] == '.' || str[ft_strlen(str) - 1] == '.') 
        return (printf(RED "Wrong argument -> %s\n" RST, str));
    if (ft_atoi(dotarg[0]) > 1 || ft_atoi(dotarg[1]) > 9 ||
            arg_counter(dotarg) != 2|| (ft_atoi(dotarg[0]) == 1 && ft_atoi(dotarg[1]) != 0))
    {
        ft_free(dotarg);
        return (printf(RED "Should be in range [0.0,1.0]: %s\n" RST, str));
    }
    return (OK);
}

int check_ambient(char **ambient, int argc/*, t_data *data*/)
{
    printf("argc == %d\n", argc);
    if (argc != 3)
        return (print_error("Wrong N of arguments\n"));
    if (check_dot(ambient[1]))
        return (KO);
    return (OK);
}
