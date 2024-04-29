#include "parser.h"
#include "../../lib/vector/vector.h"

// function that checks the id and init all the objs
int	check_type(t_data *data, char **matrix)
{
	int	len;
    int retval;

	len = ft_strlen(matrix[0]);
    retval = is_valid_char(matrix);
	if (retval)
        return (print_matrix_error(matrix, retval), KO);
    if (!ft_strncmp(matrix[0], "A", len))
    {
        printf("Hey found ambient light\n");
        if (check_ambient(matrix, arg_counter(matrix)) == KO)
            return (KO);
        init_ambient(data->ambient, matrix);
        // printf("ambient->ratio = %f\n", data->ambient->ratio);
        // printf("ambient->rgb.r = %d\n", data->ambient->rgb.r);
        // printf("ambient->rgb.g = %d\n", data->ambient->rgb.g);
        // printf("ambient->rgb.b = %d\n", data->ambient->rgb.b);
    }
    else if (!ft_strncmp(matrix[0], "L", len))
    {
        printf("Hey found Light\n");
        if (check_light(matrix, arg_counter(matrix)) == KO)
            return (KO);
        init_light(data->light, matrix);
        // printf("light->ratio = %f\n", data->light->ratio);
        // printf("light->rgb.r = %d\n", data->light->rgb.r);
        // printf("light->rgb.g = %d\n", data->light->rgb.g);
        // printf("light->rgb.b = %d\n", data->light->rgb.b);
        // print_vec(data->light->coordinates, "light->coordinates");
    }
    else if (!ft_strncmp(matrix[0], "C", len))
    {
        printf("Hey found camera here\n");
        if (check_camera(matrix, arg_counter(matrix)))
            return (KO);
        camera_init(data->camera, matrix);
    }
    else if (!ft_strncmp(matrix[0], "sp", len))
    {
        printf("Hey found a sphere\n"); 
        if (check_obj(matrix, arg_counter(matrix), SP))
            return (KO);
        init_obj(&(data->obj), matrix, SP);
    }
    else if (!ft_strncmp(matrix[0], "pl", len))
    {
        printf("Hey found a plane\n"); 
        if (check_obj(matrix, arg_counter(matrix), PL))
            return (KO);
        init_obj(&(data->obj), matrix, PL);
    }
    else if (!ft_strncmp(matrix[0], "cy", len))
    {
        printf("Hey found a cylinder\n");
        if (check_obj(matrix, arg_counter(matrix), CY))
            return (KO);
    }
    else
    {
        printf(RED "Error\nINVALID ID:"RST" \"%s\"\n", matrix[0]);
        return (KO);
    }
	return (OK);
}
