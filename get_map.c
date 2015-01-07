/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/14 11:40:41 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/07 17:09:28 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	**map_to_str(int fd, size_t *i)
{
	char	**map;
	char	*line;
	int		ret;
	size_t	len;

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
		if (*i == 0)
			len = count_nb(line);
		else
		{
			if (count_nb(line) != len)
			{
				ft_putstr_fd("Wrong number of columns at line ", 2);
				ft_putnbr_fd(*i + 1, 2);
				ft_putchar_fd('\n', 2);
				exit(EXIT_FAILURE);
			}
		}
		map[*i] = (char *)malloc_me((ft_strlen(line) + 1)* sizeof(char));
		map[*i] = line;
		map[*i][ft_strlen(line)] = '\0';
		(*i)++;
	}
	return (map);
}

t_env	get_map(char **map, t_env e, size_t lines)
{
	char	**line;
	size_t	i;
	size_t	j;

	j = 0;
	while (j != lines)
	{
		e.x = 0;
		i = 0;
		e.map[e.y] = (t_point *)malloc_me(count_nb(map[j]) * sizeof(t_point));
		line = ft_strsplit(map[j], ' ');
		while (i != count_nb(map[j]))
		{
			e.map[e.y][e.x].z = ft_atoi(line[i]);
		 	e = get_coord(e, e.y, e.x);
		 	i++;
		 	e.x++;
		}
		e.y++;
		j++;
		//free(line);
	}
	return (e);
}

t_env	init_e(int ac, char **av)
{
	t_env	e;

	e.x = 0;
	e.y = 0;
	e.x_mv = 350;
	e.y_mv = 50;
	e.rot = 0;
	e.z_scale = 0.15;
	e.iso = 1;
	if (ac == 4 && ft_atoi(av[2]) > 0 && ft_atoi(av[3]) > 0)
	{
		e.x_win = ft_atoi(av[2]);
		e.y_win = ft_atoi(av[3]);
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
	e.map = (t_point **)malloc_me(lines * sizeof(t_point *));
	e = get_map(map, e, lines);
	while (lines-- != 0)
		free(map[lines]);
	free(map);
	fdf(e);
	return (0);
}
