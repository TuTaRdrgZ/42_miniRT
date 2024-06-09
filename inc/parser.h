/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 01:31:08 by bautrodr          #+#    #+#             */
/*   Updated: 2024/06/09 18:44:10 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "miniRT.h"
# include <fcntl.h>
# include <stdbool.h>
# define OK 0
# define KO -1
# define SP 0
# define PL 1
# define CY 2

int		is_valid_filetype(char *str);
int		read_file(t_data *data, char const *filename);
void	trim_matrix(char **matrix, char *s);
int		check_type(t_data *data, char **matrix);
void	ft_free(char **matrix);
int		is_valid_char(char **matrix);
int		is_valid_filetype(char *str);
int		print_error(char *error);
int		arg_counter(char **matrix);
int		check_ambient(char **ambient, int argc);
char	*ft_strtrimfree(char *str, char *s);
void	print_matrix_error(char **matrix, int arg);
int		check_camera(char **camera, int argc);
int		check_obj(char **matrix, int argc, int type);
int		check_normalized_vector(char *str);

int		check_light(char **light, int argc);
int		check_rgb(char *str);
int		check_coordinates(char *str);
int		check_dot(char *s, int i, int j, int c);
int		check_negative(char *str);
int		check_ratio(char *str);
int		check_duplicated(t_data *data);
float	check_diameter(char *str);
#endif
