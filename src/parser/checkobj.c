#include "parser.h"

int	check_sphere(char **sphere);
int	check_plane(char **plane);
int	check_cylinder(char **cylinder);

int	check_obj(char **matrix, int argc, int type)
{
	if ((argc != 4 && (type == SP || type == PL)) || (type == CY && argc != 6))
		return (print_error("Wrong N of obj arguments\n"));
	if (type == SP)
		if (check_sphere(matrix))
			return (KO);
	if (type == PL)
		if (check_plane(matrix))
			return (KO);
	if (type == CY)
		if (check_cylinder(matrix))
			return (KO);
	return (OK);
}

int	check_sphere(char **sphere)
{
	if (check_coordinates(sphere[1]))
		return (KO);
	if (check_diameter(sphere[2]) == KO)
		return (KO);
	if (check_rgb(sphere[3]))
		return (KO);
	return (OK);
}

int	check_plane(char **plane)
{
	if (check_coordinates(plane[1]))
		return (KO);
	if (check_normalized_vector(plane[2]))
		return (KO);
	if (check_rgb(plane[3]))
		return (KO);
	return (OK);
}

int	check_cylinder(char **cylinder)
{
	if (check_coordinates(cylinder[1]))
		return (KO);
	if (check_normalized_vector(cylinder[2]))
		return (KO);
	if (check_diameter(cylinder[3]) < 0)
		return (KO);
	if (check_diameter(cylinder[4]) < 0) // actually checks the height
		return (KO);
	if (check_rgb(cylinder[5]))
		return (KO);
	return (OK);
}
