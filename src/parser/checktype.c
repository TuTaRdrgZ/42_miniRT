#include "parser.h"

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
        printf("Hey found ambient light\n"); // init_ambient(matrix, data);
        if (check_ambient(matrix, arg_counter(matrix)) == KO)
            return (KO);
    }
    else if (!ft_strncmp(matrix[0], "L", len))
    {
        printf("Hey found Light\n"); // init_light(matrix, data);
        if (check_light(matrix, arg_counter(matrix)) == KO)
            return (KO);
    }
    else if (!ft_strncmp(matrix[0], "C", len))
    {
        printf("Hey found camera here\n"); // init_camera()
        if (check_camera(matrix, arg_counter(matrix)))
            return (KO);
        camera_init(data->camera);
    }
    else if (!ft_strncmp(matrix[0], "sp", len))
    {
        printf("Hey found a sphere\n"); // init_obj(data, "sphere");
        if (check_obj(matrix, arg_counter(matrix), SP))
            return (KO);
        init_sphere(matrix); 
    }
    else if (!ft_strncmp(matrix[0], "pl", len))
    {
        printf("Hey found a plane\n"); // init_obj(data, "sphere");
        if (check_obj(matrix, arg_counter(matrix), PL))
            return (KO);
        init_plane(matrix);
    }
    else if (!ft_strncmp(matrix[0], "cy", len))
    {
        printf("Hey found a cylinder\n"); // init_obj(data, "sphere");
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
