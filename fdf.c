/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/10 09:41:55 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/27 15:50:01 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_segment(t_env e, t_point p1, t_point p2, int pos)
{
	float	dx;
	float	dy;
	float	a;
	float	b;
	float	flt;

	dy = p2.y - p1.y;
	dx = p2.x - p1.x;
	if (dx != 0)
		a = dy / dx;
	b = p1.y - a * p1.x;
	if (pos == RIGHT)
	{
		while (++p1.x != p2.x)
		{
			flt = a * (float)p1.x + b;
			p1.y = (int)roundf(flt);
			if (p1.z != 0 || p2.z != 0)
				mlx_pixel_put(e.mlx, e.win, p1.x, p1.y, 0xff0000);
			else
				mlx_pixel_put(e.mlx, e.win, p1.x, p1.y, 0x00df00);
		}
	}
	else if (pos == DOWN)
	{
		while (++p1.y != p2.y)
		{
			if (dx == 0)
				p1.x = p2.x;
			else
			{
				flt = ((float)p1.y - b) / a;
				p1.x = (int)roundf(flt);
			}
			if (p1.z != 0 || p2.z != 0)
				mlx_pixel_put(e.mlx, e.win, p1.x, p1.y, 0xff0000);
			else
				mlx_pixel_put(e.mlx, e.win, p1.x, p1.y, 0x00df00);
		}
	}
}

void	line(t_env e, int x, int y, int pos)
{
	t_point	p1;
	t_point	p2;

	p1 = e.map[y][x];
	if (pos == LEFT)
		p2 = e.map[y][x - 1];
	if (pos == UP)
		p2 = e.map[y - 1][x];
	if (pos == RIGHT)
		p2 = e.map[y][x + 1];
	if (pos == DOWN)
		p2 = e.map[y + 1][x];
	draw_segment(e, p1, p2, pos);
}

void	point_and_line(t_env e, int x, int y)
{
	int		z;

	z = e.map[y][x].z;
	if (z == 0)
		mlx_pixel_put(e.mlx, e.win, e.map[y][x].x, e.map[y][x].y, 0xffffff);
	else
		mlx_pixel_put(e.mlx, e.win, e.map[y][x].x, e.map[y][x].y, 0xff0000);
	if (x != e.x && x != e.x - 1)
		line(e, x, y, RIGHT);
	if (y != e.y && y != e.y - 1)
		line(e, x, y, DOWN);
}

void	draw_window(t_env *e)
{
	int		x;
	int		y;

	x = 0;
	while (x != e->x)
	{
		y = -1;
		while (++y != e->y)
			point_and_line(*e, x, y);
		x++;
	}
}

int		expose_hook(t_env *e)
{
	draw_window(e);
	return (0);
}

int		key_hook(int keycode, t_env *e)
{
	(void)e;
	if (keycode == 65307)
		exit(EXIT_SUCCESS);
	return (0);
}

void	fdf(t_env e)
{
	mlx_expose_hook(e.win, expose_hook, &e);
	mlx_key_hook(e.win, key_hook, &e);
	mlx_loop(e.mlx);
}
