/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/10 09:41:55 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/10 09:58:59 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		main(int argc, char **argv)
{
	void	*p_mlx;
	void	*win;
	int		x;
	int		y;

	(void)argc;
	(void)argv;
	x = 100;
	p_mlx = mlx_init();
	win = mlx_new_window(p_mlx, 400, 400, "fdf 42");
	while (x != 200)
	{
		y = 100;
		while (y != 200)
		{
			mlx_pixel_put(p_mlx, win, x, y, 0xff0000);
			usleep(500);
			y++;
		}
		x++;
	}
	sleep(5);
	(void)win;
	return (0);
}