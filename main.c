/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/10 09:41:55 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/14 11:37:21 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_window(void *p_mlx, void *p_win)
{
	int		x;
	int		y;

	x = 100;
	while (x != 200)
	{
		y = 100;
		while (y != 200)
		{
			mlx_pixel_put(p_mlx, p_win, x, y, 0xff0000);
			y++;
		}
		x++;
	}
}

int		expose_hook(t_fdf *env)
{
	draw_window(env->mlx, env->win);
	return (0);
}

int		key_hook(int keycode, t_fdf *env)
{
	(void)env;
	ft_putnbr(keycode);
	ft_putstr("\n");
	if (keycode == 65307)
		exit(EXIT_SUCCESS);
	return (0);
}

int		main(int argc, char **argv)
{
	t_fdf	env;

	(void)argc;
	(void)argv;
	env.mlx = mlx_init();
	env.win = mlx_new_window(env.mlx, 400, 400, "fdf 42");
	mlx_expose_hook(env.win, expose_hook, &env);
	mlx_key_hook(env.win, key_hook, &env);
	mlx_loop(env.mlx);
	return (0);
}