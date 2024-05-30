#include "parser.h"

// free and get the next line
static char	*new_line(char **matrix, char *line, int fd)
{
	char	*new;

	new = get_next_line(fd);
	ft_free(matrix);
	free(line);
	return (new);
}

int	read_file(t_data *data, char const *filename)
{
	int		fd;
	char	*line;
	char	**matrix_line;
    
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (print_error("Failed to open file\n"));
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line[0] == '\n' || line[0] == '\0' || line[0] == '#') // checkea si la linea esta vacia o es un comentario (#)
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
        line = ft_strtrimfree(line, " \n\t");
		matrix_line = ft_split(line, ' ');
		if (check_type(data, matrix_line) == KO) // checkeamos el tipo de objeto y que los parametros sean validos
		{
			free(line);
			ft_free(matrix_line);
			return (KO);
		}
		line = new_line(matrix_line, line, fd);
	}
	free(line);
	close(fd);
	return (OK);
}
