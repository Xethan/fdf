/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/14 11:40:41 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/06 12:48:03 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	*malloc_me(size_t size)
{
	void	*content;

	if (size == 0)
		size = 1;
	content = malloc(size);
	if (content == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	return (content);
}

size_t	how_many_numbers(char *line)
{
	int		i;
	size_t	ret;

	i = 0;
	ret = 0;
	while (line[i])
	{
		while (line[i] && !ft_isdigit(line[i]))
			i++;
		while (line[i] && ft_isdigit(line[i]))
			i++;
		ret++;
	}
	return (ret);
}

char	**restralloc(char **map, int length)
{
	char	**tmp;
	int		i;

	i = -1;
	tmp = map;
	map = (char **)malloc_me((length + 1) * sizeof(char*));
	while (++i != length)
		map[i] = tmp[i];
	free(tmp);
	return (map);
}

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
		map = restralloc(map, *i);
		if ((ret = get_next_line(fd, &line) == 1) == -1)
		{
			 ft_putendl_fd("Error get_next_line", 2);
			 exit(EXIT_FAILURE);
		}
		if (!line[0] && ret == 0)
			return (map);
		if (*i == 0)
			len = how_many_numbers(line);
		else
		{
			if (how_many_numbers(line) != len)
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

t_env	get_map(char **map, t_env e)
{
	int		i;
	int		j;

	j = 0;
	while (map[j])
	{
		e.x = 0;
		i = 0;
		e.map[e.y] = (t_point *)malloc_me(how_many_numbers(map[j]) * sizeof(t_point));
		while (map[j][i])
		{
			while (map[j][i] && !ft_isdigit(map[j][i]))
				i++;
			e.map[e.y][e.x].z = ft_atoi(map[j] + i);
			e.map[e.y][e.x].x = e.x_mv + e.scale * 2 * (e.x - e.y);
			e.map[e.y][e.x].y = e.y_mv + e.scale * (e.x + (e.y - e.z_scale * e.map[e.y][e.x].z));
			i += ft_nbrlen(e.map[e.y][e.x].z);
			e.x++;
		}
		e.y++;
		j++;
	}
	return (e);
}

int		main(int argc, char **argv)
{
	t_env	e;
	char	**map;
	size_t	lines;
	int		fd;

	e.x = 0;
	e.y = 0;
	e.x_mv = 350;
	e.y_mv = 50;
	e.z_scale = 0.15;
	e.iso = 1;
	if (argc == 1)
	{
		ft_putstr_fd("fdf: No arguments\n", 2);
		return (0);
	}
	if ((fd = open(argv[1], O_RDONLY)) == -1)
	{
		ft_putstr_fd("fdf: ", 2);
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}
	map = map_to_str(fd, &lines);
	e.scale = (lines > how_many_numbers(map[0])) ? 300 / lines : 300 / how_many_numbers(map[0]);
	if (e.scale == 0)
		e.scale = 1;
	e.map = (t_point **)malloc_me(lines * sizeof(t_point *));
	e = get_map(map, e);
	while (lines-- != 0)
		free(map[lines]);
	free(map);
	fdf(e);
	return (0);
}
