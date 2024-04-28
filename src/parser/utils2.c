#include "parser.h"

void    print_matrix_error(char **matrix, int arg)
{
    int i;

    i = -1;
    while (matrix[++i])
    {
        if (i == arg)
            printf(RED"[%s] "RST, matrix[i]);
        else if (arg == -1)
            printf(RED"%s "RST, matrix[i]);
        else
            printf("%s ", matrix[i]);
    }
    printf("\n");
}

// remember: i = -1; j = 0; c = -1;
int check_dot(char *s, int i, int j, int c)
{
	while (s[++i])
	{
		if (s[i] == '.')
			j++;
	}
	i = -1;
	while (s[++i])
	{
		if ((i == 0 && s[i] == '.') || (j > 1))
            return (printf(RED"Error\n"RST"Invalid coordinate: %s\n", s), KO);
		else if (s[i] == '.' && (ft_isdigit(s[i - 1]) != 1
				|| ft_isdigit(s[i + 1]) != 1))
            return (printf(RED"Error\n"RST"Invalid coordinate: %s\n", s), KO);
		else if (s[i] == '.')
			c = i + 4;
		else if (i == c)
            return (printf(RED"Error\n"RST"Invalid coordinate: %s\n", s), KO);
	}
    return (OK);
}

int check_negative(char *str)
{
    int i;

    i = 0;
    if (!str)
        return (OK);
    while (str[i] != '\0')
    {
        if (str[i] == '-' && i != 0)
            return (printf(RED"Error\nBad sign position: [%s]\n"RST, str), KO);
        if (str[0] == '-' && !str[1])
            return (printf(RED"Error\nNo numeric chars found after '-': [%s]\n"RST, str), KO);
        i++;
    }
    return (OK);
}

int check_ratio(char *str)
{
    char    **dotarg;

    dotarg = ft_split(str, '.');
    if (!dotarg|| !dotarg[0] || !dotarg[1] || ft_strlen(str) < 3
            || str[0] == '.' || str[ft_strlen(str) - 1] == '.') 
        return (printf(RED "Error\n" RST "Wrong argument: "), 1);
    if (ft_atoi(dotarg[0]) < 0 || ft_atoi(dotarg[1]) < 0 ||ft_atoi(dotarg[0]) > 1.0
            || ft_atoi(dotarg[1]) > 9 || arg_counter(dotarg) != 2
            || (ft_atoi(dotarg[0]) == 1 && ft_atoi(dotarg[1]) != 0))
    {
        ft_free(dotarg);
        return (printf(RED "Error\n"RST"Ratio should be in range [0.0,1.0]: "), 1);
    }
    ft_free(dotarg);
    return (OK);
}
