/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/10 09:41:55 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/11 14:20:07 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_window(t_env *e)
{
	size_t	x;
	size_t	y;

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
	size_t	i;

	if ((keycode >= 65361 && keycode <= 65364)
		|| keycode == 65451 || keycode == 65453 || keycode == 65293
		|| keycode == 65455 || keycode == 65450 || keycode == 114)
	{
		*e = recompute_map(*e, keycode);
		*e = compute_map(*e);
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
	e.win = mlx_new_window(e.mlx, e.x_win, e.y_win, "fdf 42");
	mlx_expose_hook(e.win, expose_hook, &e);
	mlx_hook(e.win, 2, 3, key_hook, &e);
	mlx_loop(e.mlx);
}
