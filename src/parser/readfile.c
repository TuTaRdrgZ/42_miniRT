#include "parser.h"

// free and get the next line
static char	*new_line(char **matrix, char *line, int fd)
{
	char	*new;

	free(line);
	new = get_next_line(fd);
	ft_free(matrix);
	return (new);
}

static int	process_line(t_data *data, char **line, char **matrix_line, int fd)
{
	if (*line && (*line)[ft_strlen(*line) - 1] == '\n')
		(*line)[ft_strlen(*line) - 1] = '\0';
	matrix_line = ft_split_set(*line, " \t\v\f\r");
	if (!(matrix_line))
		exit(-1); // TODO : exit error
	trim_matrix(matrix_line, " \n");
	if (check_type(data, matrix_line) == KO)
	{
		free(*line);
		ft_free(matrix_line);
		close(fd);
		return (-1);
	}
	*line = new_line(matrix_line, *line, fd);
	return (0);
}

int	read_file(t_data *data, char const *filename)
{
	int		fd;
	char	*line;
	char	**matrix_line;
	int		flag;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (print_error("Failed to open file\n"));
	line = get_next_line(fd);
	matrix_line = NULL;
	while (line != NULL)
	{
		if (line[0] == '\n' || line[0] == '\0' || line[0] == '#')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		flag = process_line(data, &line, matrix_line, fd);
		if (flag == -1)
			return (KO);
	}
	free(line);
	close(fd);
	return (OK);
}
