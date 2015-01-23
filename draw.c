/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/28 12:26:49 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/23 14:18:53 by ncolliau         ###   ########.fr       */
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
		p2.z = (p2.z > p1.z) ? p2.z : p1.z;
		ft_pixel_put(e, p2.z, p1.x, p1.y);
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
		p2.z = (p2.z > p1.z) ? p2.z : p1.z;
		ft_pixel_put(e, p2.z, p1.x, p1.y);
		(p2.y - p1.y > 0) ? p1.y++ : p1.y--;
	}
}

void	draw_segment(t_env e, t_point p1, t_point p2)
{
	float	dx;
	float	dy;
	float	a;

	a = 0;
	dy = p2.y - p1.y;
	dx = p2.x - p1.x;
	if (dx != 0)
		a = dy / dx;
	if (dx != 0)
		right_draw(e, p1, p2, a);
	if (dy != 0)
		down_draw(e, p1, p2, a);
}

int		is_map(t_env e, int x, int y)
{
	int		abciss;
	int		ordinat;

	abciss = e.map[y][x].x;
	ordinat = e.map[y][x].y;
	if (abciss < 0 || abciss > e.x_win || ordinat < 0 || ordinat > e.y_win)
		return (0);
	return (1);
}

void	point_and_line(t_env e, size_t x, size_t y)
{
	ft_pixel_put(e, e.map[y][x].z, e.map[y][x].x, e.map[y][x].y);
	if (x != e.x - 1)
		if (is_map(e, x, y) || is_map(e, x + 1, y))
			draw_segment(e, e.map[y][x], e.map[y][x + 1]);
	if (y != e.y - 1)
		if (is_map(e, x, y) || is_map(e, x, y + 1))
			draw_segment(e, e.map[y][x], e.map[y + 1][x]);
}
