/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/04 14:42:35 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/11 17:12:00 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_env	reset(t_env e)
{
	if (e.y_win / e.y < e.x_win / e.x)
		e.scale = e.y_win / 3 / e.y;
	else
		e.scale = e.x_win / 3 / e.x;
	if (e.scale < 0.2)
		e.scale = 0.2;
	e.z_scale = 0.15;
	e.x_mv = e.x_win / 2 - e.scale * (e.x - e.y);
	e.y_mv = e.y_win / 4;
	return (e);
}

t_env	change_project(t_env e)
{
	if (e.iso == 1)
		e.iso = 0;
	else
		e.iso = 1;
	return (e);
}

t_env	scale_z(t_env e, int inc)
{
	e.z_scale += 0.05 * inc;
	return (e);
}

t_env	zoom(t_env e, int inc)
{
	if (e.scale <= 1)
	{
		if (inc == 1 || e.scale > 0.2)
			e.scale += 0.1 * inc;
	}
	else
		e.scale += 0.5 * inc;
	return (e);
}

t_env	move(t_env e, int inc, int which)
{
	if (which == X)
		e.x_mv += 10 * inc;
	else if (which == Y)
		e.y_mv += 10 * inc;
	return (e);
}
