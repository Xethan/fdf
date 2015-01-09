/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/04 14:42:35 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/09 17:28:59 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_env	reset(t_env e)
{
	e.scale = (e.y > e.x) ? e.y_win / 3 / e.y : e.x_win / 3 / e.x;
	if (e.scale < 0.5)
		e.scale = 0.5;
	e.z_scale = 0.15;
	e.x_mv = e.x_win / 2 - e.scale * (e.x - e.y);
	e.y_mv = e.y_win / 4;
	e = compute_map(e);
	return (e);
}

t_env	change_project(t_env e)
{
	if (e.iso == 1)
		e.iso = 0;
	else
		e.iso = 1;
	e = compute_map(e);
	return (e);
}

t_env	scale_z(t_env e, int inc)
{
	e.z_scale += 0.05 * inc;
	e = compute_map(e);
	return (e);
}

t_env	zoom(t_env e, int inc)
{
	if (inc == 1 || e.scale > 0.5)
		e.scale += 0.5 * inc;
	e = compute_map(e);
	return (e);
}

t_env	move(t_env e, int inc, int which)
{
	size_t	x;
	size_t	y;

	if (which == X)
		e.x_mv += 10 * inc;
	else if (which == Y)
		e.y_mv += 10 * inc;
	x = 0;
	while (x != e.x)
	{
		y = 0;
		while (y != e.y)
		{
			if (which == X)
				e.map[y][x].x += 10 * inc;
			else
				e.map[y][x].y += 10 * inc;
			y++;
		}
		x++;
	}
	return (e);
}
