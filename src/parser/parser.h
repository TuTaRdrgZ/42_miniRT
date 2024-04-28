#ifndef PARSER_H
#define PARSER_H
#include <stdio.h>
#include <string.h>
#include "../../inc/miniRT.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#define OK 0
#define KO 1

int is_valid_filetype(char *str);
int	read_file(/*t_data *data,*/ char const *filename);
char	*new_line(char **matrix, char *line, int fd);
void	trim_matrix(char **matrix, char *s); //probably wont need it
int	check_type(/*t_data *data, */ char **matrix);
void	ft_free(char **matrix);
int	is_valid_char(char **matrix);
int	is_valid_filetype(char *str);
int	print_error(char *error);
int arg_counter(char **matrix);
int check_ambient(char **ambient, int argc/*, t_data *data*/);
char *ft_strtrimfree(char *str, char *s);
void    print_matrix_error(char **matrix, int arg);
int check_camera(char **camera, int argc);

int check_light(char **light, int argc);
int check_rgb(char *str);
int check_coordinates(char *str);
int check_dot(char *s, int i, int j, int c);
int check_negative(char *str);
int check_ratio(char *str);
#endif
