/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/04 14:42:35 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/06 12:48:31 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_env	reset(t_env e)
{
	int		x;
	int		y;

	e.scale = 15;
	e.z_scale = 0.15;
	e.x_mv = 350;
	e.y_mv = 50;
	x = 0;
	while (x != e.x)
	{
		y = 0;
		while (y != e.y)
		{
			if (e.iso == 0)
			{
				e.map[y][x].x = e.x_mv - 300 + (14 * e.z_scale) * e.map[y][x].z + x * e.scale * 2;
				e.map[y][x].y = e.y_mv - (14 * e.z_scale) * e.map[y][x].z + y * e.scale * 2;
			}
			else
			{
				e.map[y][x].x = e.x_mv + e.scale * 2 * (x - y);
				e.map[y][x].y = e.y_mv + e.scale * (x + (y - e.z_scale * e.map[y][x].z));
			}
			y++;
		}
		x++;
	}
	return (e);
}

t_env	change_project(t_env e)
{
	int		x;
	int		y;

	x = 0;
	while (x != e.x)
	{
		y = 0;
		while (y != e.y)
		{
			if (e.iso == 1)
			{
				e.map[y][x].x = e.x_mv - 300 + (14 * e.z_scale) * e.map[y][x].z + x * e.scale * 2;
				e.map[y][x].y = e.y_mv - (14 * e.z_scale) * e.map[y][x].z + y * e.scale * 2;
			}
			else
			{
				e.map[y][x].x = e.x_mv + e.scale * 2 * (x - y);
				e.map[y][x].y = e.y_mv + e.scale * (x + (y - e.z_scale * e.map[y][x].z));
			}
			y++;
		}
		x++;
	}
	if (e.iso == 1)
		e.iso = 0;
	else
		e.iso = 1;
	return(e);
}

t_env	scale_z(t_env e, int inc)
{
	int		x;
	int		y;

	e.z_scale += 0.05 * inc;
	x = 0;
	while (x != e.x)
	{
		y = 0;
		while (y != e.y)
		{
			if (e.iso == 0)
			{
				e.map[y][x].x = e.x_mv - 300 + (14 * e.z_scale) * e.map[y][x].z + x * e.scale * 2;
				e.map[y][x].y = e.y_mv - (14 * e.z_scale) * e.map[y][x].z + y * e.scale * 2;
			}
			else
			{
				e.map[y][x].x = e.x_mv + e.scale * 2 * (x - y);
				e.map[y][x].y = e.y_mv + e.scale * (x + (y - e.z_scale * e.map[y][x].z));
			}
			y++;
		}
		x++;
	}
	return (e);
}

t_env	zoom(t_env e, int inc)
{
	int		x;
	int		y;

	if (inc == 1 || e.scale > 1)
		e.scale += inc;
	x = 0;
	while (x != e.x)
	{
		y = 0;
		while (y != e.y)
		{
			if (e.iso == 0)
			{
				e.map[y][x].x = e.x_mv - 300 + (14 * e.z_scale) * e.map[y][x].z + x * e.scale * 2;
				e.map[y][x].y = e.y_mv - (14 * e.z_scale) * e.map[y][x].z + y * e.scale * 2;
			}
			else
			{
				e.map[y][x].x = e.x_mv + e.scale * 2 * (x - y);
				e.map[y][x].y = e.y_mv + e.scale * (x + (y - e.z_scale * e.map[y][x].z));
			}
			y++;
		}
		x++;
	}
	return (e);
}

t_env	rotate(t_env e, int inc)
{
	int		x;
	int		y;

	e.x_mv += 5 * inc;
	e.y_mv -= 20 * inc;
	x = 0;
	while (x != e.x)
	{
		y = 0;
		while (y != e.y)
		{
			e.map[y][x].x += 5 * inc;
			e.map[y][x].y -= 20 * inc;
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
	else
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
