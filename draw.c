/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/28 12:26:49 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/06 12:48:38 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	right_draw(t_env e, t_point p1, t_point p2, float a)
{
	float	flt;
	float	b;

	b = p1.y - a * p1.x;
	(p2.x - p1.x > 0) ? p1.x++ : p1.x--;
	while (p1.x != p2.x)
	{
		flt = a * p1.x + b;
		p1.y = (int)roundf(flt);
		if (p1.z != 0 || p2.z != 0)
			mlx_pixel_put(e.mlx, e.win, p1.x, p1.y, 0xff0000);
		else
			mlx_pixel_put(e.mlx, e.win, p1.x, p1.y, 0x00df00);
		(p2.x - p1.x > 0) ? p1.x++ : p1.x--;
	}
}

void	down_draw(t_env e, t_point p1, t_point p2, float a)
{
	float	flt;
	float	b;

	b = p1.y - a * p1.x;
	(p2.y - p1.y > 0) ? p1.y++ : p1.y--;
	while (p1.y != p2.y)
	{
		if (p2.x != p1.x)
		{
			flt = (p1.y - b) / a;
			p1.x = (int)roundf(flt);
		}
		if (p1.z != 0 || p2.z != 0)
			mlx_pixel_put(e.mlx, e.win, p1.x, p1.y, 0xff0000);
		else
			mlx_pixel_put(e.mlx, e.win, p1.x, p1.y, 0x00df00);
		(p2.y - p1.y > 0) ? p1.y++ : p1.y--;
	}
}

void	draw_segment(t_env e, t_point p1, t_point p2, int pos)
{
	float	dx;
	float	dy;
	float	a;

	(void)pos;
	dy = p2.y - p1.y;
	dx = p2.x - p1.x;
	if (dx != 0)
		a = dy / dx;
	if (dx != 0)
		right_draw(e, p1, p2, a);
	if (dy != 0)
		down_draw(e, p1, p2, a);
}

void	point_and_line(t_env e, int x, int y)
{
	int		z;

	z = e.map[y][x].z;
	if (z == 0)
		mlx_pixel_put(e.mlx, e.win, e.map[y][x].x, e.map[y][x].y, 0x00df00);
	else
		mlx_pixel_put(e.mlx, e.win, e.map[y][x].x, e.map[y][x].y, 0xff0000);
	if (x != e.x - 1)
		draw_segment(e, e.map[y][x], e.map[y][x + 1], X);
	if (y != e.y - 1)
		draw_segment(e, e.map[y][x], e.map[y + 1][x], Y);
}
