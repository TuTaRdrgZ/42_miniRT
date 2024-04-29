#include "parser.h"

int check_ambient(char **ambient, int argc/*, t_data *data*/)
{
    int returnval;

    if (argc != 3)
        return (print_error("Wrong N of arguments\n"));
    returnval = check_ratio(ambient[1]);
    if (returnval)
       return (print_matrix_error(ambient, returnval), KO);
    if (check_rgb(ambient[2]))
        return (KO);
    return (OK);
}
