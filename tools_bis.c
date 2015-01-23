/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/08 19:19:31 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/23 14:59:34 by ncolliau         ###   ########.fr       */
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

void	check_map(char *line, size_t nb_nb, int nb_line)
{
	int		i;

	i = 0;
	if (count_nb(line) > nb_nb)
		ft_putstr_fd("Too many numbers at line ", 2);
	if (count_nb(line) < nb_nb)
		ft_putstr_fd("Not enough numbers at line ", 2);
	if (count_nb(line) != nb_nb)
		map_error(nb_line, line);
	while (line[i])
	{
		if (line[i] != ' ' && !ft_isdigit(line[i]))
		{
			if (!(line[i] == '-' && line[i + 1] && ft_isdigit(line[i + 1])))
			{
				ft_putstr_fd("Bad character: \"", 2);
				ft_putchar_fd(line[i], 2);
				ft_putstr_fd("\" at line ", 2);
				map_error(nb_line, line);
			}
		}
		i++;
	}
}
