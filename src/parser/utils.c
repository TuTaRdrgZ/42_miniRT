#include "parser.h"

int arg_counter(char **matrix)
{
    int i;

    i = 0;
    while (matrix[i])
        i++;
    return (i);
}

int	print_error(char *error)
{
	printf(RED "%s" RST, error);
	return (1);
}

char *ft_strtrimfree(char *str, char *s)
{
    char *new;

    new = ft_strtrim(str, s);
    if (str)
        free(str);
    return (new);
}

// apply ft_strtrim to a matrix
void	trim_matrix(char **matrix, char *s)
{
	int		i;
	char	*tmp;

	i = 0;
	while (matrix[i])
	{
		tmp = ft_strtrim(matrix[i], s);
		free(matrix[i]);
		matrix[i] = tmp;
		i++;
	}
}

void	ft_free(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}
