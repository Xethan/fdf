/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/14 11:40:41 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/11 17:11:37 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	map_error(int nb_line, char **map)
{
	ft_putnbr_nl_fd(nb_line + 1, 2);
	while (nb_line != -1)
	{
		free(map[nb_line]);
		nb_line--;
	}
	free(map);
	exit(EXIT_FAILURE);
}

char	**map_to_str(int fd, size_t *i)
{
	char	**map;
	char	*line;
	int		ret;

	*i = 0;
	ret = 1;
	while (ret == 1)
	{
		if ((ret = get_next_line(fd, &line) == 1) == -1)
		{
			ft_putendl_fd("Error get_next_line", 2);
			exit(EXIT_FAILURE);
		}
		if (!line[0] && ret == 0)
			return (map);
		map = restralloc(map, *i);
		map[*i] = ft_strdup(line);
		check_map(line, map, *i);
		free(line);
		(*i)++;
	}
	return (map);
}

t_env	get_map(char **map, t_env e, size_t lines)
{
	char	**line;

	e.map = (t_point **)malloc_me(lines * sizeof(t_point *));
	e.y = 0;
	while (e.y != lines)
	{
		e.x = 0;
		e.map[e.y] = (t_point *)malloc_me(count_nb(map[e.y]) * sizeof(t_point));
		line = ft_strsplit(map[e.y], ' ');
		while (e.x != count_nb(map[e.y]))
		{
			e.map[e.y][e.x].z = ft_atoi(line[e.x]);
			e = get_coord(e, e.y, e.x);
			free(line[e.x]);
			e.x++;
		}
		free(line);
		free(map[e.y]);
		e.y++;
	}
	free(map);
	return (e);
}

t_env	init_e(int ac, char **av, size_t x, size_t y)
{
	t_env	e;

	e.z_scale = 0.15;
	e.iso = 1;
	if (ac == 4 && ft_atoi(av[2]) > 0 && ft_atoi(av[3]) > 0)
	{
		e.x_win = ft_atoi(av[2]);
		e.x_win = (e.x_win > 2560) ? 2560 : e.x_win;
		e.x_win = (e.x_win < 100) ? 100 : e.x_win;
		e.y_win = ft_atoi(av[3]);
		e.y_win = (e.y_win > 1370) ? 1370 : e.y_win;
		e.y_win = (e.y_win < 100) ? 100 : e.y_win;
	}
	else
	{
		e.x_win = 1000;
		e.y_win = 1000;
	}
	e.scale = (e.y_win / y < e.x_win / x) ? e.y_win / 3 / y : e.x_win / 3 / x;
	if (e.scale < 0.2)
		e.scale = 0.2;
	e.x_mv = e.x_win / 2 - e.scale * (x - y);
	e.y_mv = e.y_win / 4;
	return (e);
}

int		main(int ac, char **av)
{
	t_env	e;
	char	**map;
	size_t	lines;
	int		fd;

	if (ac == 1)
	{
		ft_putstr_fd("fdf: No arguments\n", 2);
		return (0);
	}
	if ((fd = open(av[1], O_RDONLY)) == -1)
	{
		ft_putstr_fd("fdf: ", 2);
		perror(av[1]);
		exit(EXIT_FAILURE);
	}
	map = map_to_str(fd, &lines);
	e = init_e(ac, av, count_nb(map[0]), lines);
	e = get_map(map, e, lines);
	fdf(e);
	return (0);
}
