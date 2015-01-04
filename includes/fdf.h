/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/10 09:43:30 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/04 15:00:47 by ncolliau         ###   ########.fr       */
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
	int			scale;
	float		z_scale;
	int			x_mv;
	int			y_mv;
}				t_env;

t_env			get_map(int fd, t_env e);
void			*malloc_me(size_t size);

void			fdf(t_env e);

t_env			reset(t_env e);
t_env			scale_z(t_env e, int inc);
t_env			zoom(t_env e, int inc);
t_env			move(t_env e, int inc, int which);

void			point_and_line(t_env e, int x, int y);

int				get_next_line(int const fd, char **line);

#endif
