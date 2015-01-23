/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/10 09:43:30 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/23 14:50:44 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define X	1
# define Y	2
# define RED	0xAF0000
# define GREEN	0x00AF00
# define BLUE	0x0000AF

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "libft.h"
# include "get_next_line.h"

typedef struct	s_point
{
	int			x;
	int			y;
	int			z;
}				t_point;

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	t_point		**map;
	size_t		x;
	size_t		y;
	int			x_win;
	int			y_win;
	float		scale;
	float		z_scale;
	int			x_mv;
	int			y_mv;
	int			iso;
}				t_env;

void			map_error(int nb_line, char *line);

void			fdf(t_env e);

t_env			reset(t_env e);
t_env			change_project(t_env e);
t_env			scale_z(t_env e, int inc);
t_env			zoom(t_env e, int inc);
t_env			move(t_env e, int inc, int which);

void			point_and_line(t_env e, size_t x, size_t y);

void			*malloc_me(size_t size);
size_t			count_nb(char *line);
t_point			**realloc_map(t_point **map, int length);
t_env			get_coord(t_env e, int y, int x);
t_env			compute_map(t_env e);

t_env			recompute_map(t_env e, int keycode);
void			ft_pixel_put(t_env e, int z, int x, int y);
void			check_map(char *line, size_t nb_nb, int nb_line);

int				get_next_line(int const fd, char **line);

#endif
