/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/10 09:43:30 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/07 16:17:52 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define X	1
# define Y	2

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
	int			x;
	int			y;
	int			x_win;
	int			y_win;
	float		scale;
	float		z_scale;
	int			x_mv;
	int			y_mv;
	int			rot;
	int			iso;
}				t_env;

t_env			get_map(char **map, t_env e, size_t lines);

void			fdf(t_env e);

t_env			reset(t_env e);
t_env			change_project(t_env e);
t_env			scale_z(t_env e, int inc);
t_env			zoom(t_env e, int inc);
t_env			rotate(t_env e, int inc);
t_env			move(t_env e, int inc, int which);

void			point_and_line(t_env e, int x, int y);


void			*malloc_me(size_t size);
size_t			count_nb(char *line);
char			**restralloc(char **map, int length);
t_env			get_coord(t_env e, int y, int x);
t_env			compute_map(t_env e);

int				get_next_line(int const fd, char **line);

#endif
