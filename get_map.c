/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/14 11:40:41 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/08 20:30:17 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	map_error(int nb_line, char **map)
{
	ft_putstr_fd("Wrong number of columns at line ", 2);
	ft_putnbr_fd(nb_line + 1, 2);
	ft_putchar_fd('\n', 2);
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
		if (count_nb(line) != count_nb(map[0]))
			map_error(*i, map);
		free(line);
		(*i)++;
	}
	return (map);
}

t_env	get_map(char **map, t_env e, size_t lines)
{
	char	**line;

	e.map = (t_point **)malloc_me(lines * sizeof(t_point *));
	while (e.y != lines)
	{
		e.x = 0;
		e.map[e.y] = (t_point *)malloc_me(count_nb(map[e.y]) * sizeof(t_point));
		line = ft_strsplit(map[e.y], ' ');
		//line = ft_strfuncsplit(map[e.y], check_split);
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

t_env	init_e(int ac, char **av)
{
	t_env	e;

	e.x = 0;
	e.y = 0;
	e.x_mv = 350;
	e.y_mv = 50;
	e.z_scale = 0.15;
	e.iso = 1;
	if (ac == 4 && ft_atoi(av[2]) > 0 && ft_atoi(av[3]) > 0)
	{
		e.x_win = ft_atoi(av[2]);
		if (e.x_win > 2560)
			e.x_win = 2560;
		e.y_win = ft_atoi(av[3]);
		if (e.y_win > 1370)
			e.y_win = 1370;
	}
	else
	{
		e.x_win = 1000;
		e.y_win = 1000;
	}
	return (e);
}

int		main(int ac, char **av)
{
	t_env	e;
	char	**map;
	size_t	lines;
	int		fd;

	e = init_e(ac, av);
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
	e.scale = (lines > count_nb(map[0])) ? 300 / lines : 300 / count_nb(map[0]);
	if (e.scale < 0.5)
		e.scale = 0.5;
	e = get_map(map, e, lines);
	fdf(e);
	return (0);
}
