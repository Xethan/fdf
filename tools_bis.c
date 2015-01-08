/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/08 19:19:31 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/08 20:29:33 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_env	recompute_map(t_env e, int keycode)
{
	if (keycode == 65455)
		e = scale_z(e, -1);
	if (keycode == 65450)
		e = scale_z(e, 1);
	if (keycode == 65451)
		e = zoom(e, 1);
	if (keycode == 65453)
		e = zoom(e, -1);
	if (keycode == 65361)
		e = move(e, 1, X);
	if (keycode == 65363)
		e = move(e, -1, X);
	if (keycode == 65362)
		e = move(e, 1, Y);
	if (keycode == 65364)
		e = move(e, -1, Y);
	if (keycode == 114)
		e = reset(e);
	if (keycode == 65293)
		e = change_project(e);
	return (e);
}

void	ft_pixel_put(t_env e, int z, int x, int y)
{
	if (z < 0)
		mlx_pixel_put(e.mlx, e.win, x, y, BLUE);
	if (z == 0)
		mlx_pixel_put(e.mlx, e.win, x, y, GREEN);
	if (z > 0)
		mlx_pixel_put(e.mlx, e.win, x, y, RED);
}

int		check_split(char c)
{
	if (ft_isdigit(c) || c == '-')
		return (0);
	return (1);
}