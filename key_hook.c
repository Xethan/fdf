/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/04 14:42:35 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/06 15:06:10 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_env	reset(t_env e)
{
	e.scale = 15;
	e.z_scale = 0.15;
	e.x_mv = 350;
	e.y_mv = 50;
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
	return(e);
}

t_env	scale_z(t_env e, int inc)
{
	e.z_scale += 0.05 * inc;
	e = compute_map(e);
	return (e);
}

t_env	zoom(t_env e, int inc)
{
	if (inc == 1 || e.scale > 1)
		e.scale += inc;
	e = compute_map(e);
	return (e);
}

t_env	rotate(t_env e, int inc)
{
	int		x;
	int		y;
	
	e.rot += inc * 2;
	x = 0;
	while (x != e.x)
	{
		y = 0;
		while (y != e.y)
		{
			e.map[y][x].x = e.map[y][x].x * cos(e.rot) - e.map[y][x].y * sin(e.rot);
			e.map[y][x].y = e.map[y][x].x * sin(e.rot) + e.map[y][x].y * cos(e.rot);
			y++;
		}
		x++;
	}
	return (e);
}

t_env	move(t_env e, int inc, int which)
{
	int		x;
	int		y;

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
