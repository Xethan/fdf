/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/10 09:41:55 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/28 15:30:33 by ncolliau         ###   ########.fr       */
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

	(void)e;
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
	mlx_expose_hook(e.win, expose_hook, &e);
	mlx_key_hook(e.win, key_hook, &e);
	mlx_loop(e.mlx);
}
