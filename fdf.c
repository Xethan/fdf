/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/10 09:41:55 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/06 12:48:45 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	int		i;

	//ft_putnbr(keycode);
	//ft_putendl("");
	if (keycode == 65455)
		*e = scale_z(*e, -1);
	if (keycode == 65450)
		*e = scale_z(*e, 1);
	if (keycode == 65451)
		*e = zoom(*e, 1);
	if (keycode == 65453)
		*e = zoom(*e, -1);
	if (keycode == 65361)
		*e = move(*e, -1, X);
	if (keycode == 65363)
		*e = move(*e, 1, X);
	if (keycode == 65364)
		*e = move(*e, 1, Y);
	if (keycode == 65362)
		*e = move(*e, -1, Y);
	//if (keycode == 65365)
	//	*e = rotate(*e, -1);
	//if (keycode == 65366)
	//	*e = rotate(*e, 1);
	if (keycode == 114)
		*e = reset(*e);
	if (keycode == 65293)
		*e = change_project(*e);
	if ((keycode >= 65361 && keycode <= 65364)
		|| keycode == 65451 || keycode == 65453 || keycode == 65293
		|| keycode == 65455 || keycode == 65450 || keycode == 114)
		//|| keycode == 65365 || keycode == 65366)
	{
		mlx_clear_window(e->mlx, e->win);
		draw_window(e);
	}
	if (keycode == 65307)
	{
		i = 0;
		while (i != e->y)
		{
			free(e->map[i]);
			i++;
		}
		free(e->map);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

void	fdf(t_env e)
{
	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, 1000, 1000, "fdf 42");
	mlx_expose_hook(e.win, expose_hook, &e);
	mlx_key_hook(e.win, key_hook, &e);
	mlx_loop(e.mlx);
}
