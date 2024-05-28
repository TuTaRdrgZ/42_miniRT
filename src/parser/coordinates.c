#include "parser.h"

int	check_coordinates(char *str)
{
	char	**commas;
	int		i;

	commas = ft_split(str, ',');
	if (!commas)
		return (printf("Malloc failed\n"), KO);
	if (arg_counter(commas) != 3)
		return (printf(RED "Error\n" RST "Invalid coordinates: %s\n", str),
			ft_free(commas), KO);
	if (check_dot(commas[0], -1, 0, -1) || check_dot(commas[1], -1, 0, -1)
		|| check_dot(commas[2], -1, 0, -1))
		return (ft_free(commas), KO);
	i = -1;
	while (++i <= 3)
		if (check_negative(commas[i]))
			return (ft_free(commas), KO);
	ft_free(commas);
	return (OK);
}
