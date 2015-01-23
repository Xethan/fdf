/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/14 11:40:41 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/23 15:30:52 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	map_error(int nb_line, char *line)
{
	ft_putnbr_nl_fd(nb_line + 1, 2);
	free(line);
	exit(EXIT_FAILURE);
}

t_env	line_to_coord(t_env e, char *line)
{
	char	**str;

	e.map = realloc_map(e.map, e.y);
	str = ft_sizesplit(line, ' ', &(e.x));
	e.map[e.y] = (t_point *)malloc(e.x * sizeof(t_point));
	while (e.x-- != 0)
		e.map[e.y][e.x].z = ft_atoi(str[e.x]);
	e.x = count_nb(line);
	ft_freetab(str, e.x);
	return (e);
}

t_env	map_to_str(int fd, t_env e)
{
	char	*line;
	int		ret;
	int		nb_nb;

	e.y = 0;
	ret = 1;
	while (ret == 1)
	{
		if ((ret = get_next_line(fd, &line)) == -1)
		{
			ft_putendl_fd("Error get_next_line", 2);
			exit(EXIT_FAILURE);
		}
		if (line[0])
		{
			e = line_to_coord(e, line);
			if (e.y == 0)
				nb_nb = e.x;
			check_map(line, nb_nb, e.y);
			free(line);
			e.y++;
		}
	}
	return (e);
}

t_env	init_e(int ac, char **av, t_env e)
{
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
	if (e.y_win / e.y < e.x_win / e.x)
		e.scale = e.y_win / 3 / e.y;
	else
		e.scale = e.x_win / 3 / e.x;
	if (e.scale < 0.2)
		e.scale = 0.2;
	e.x_mv = e.x_win / 2 - e.scale * (e.x - e.y);
	e.y_mv = e.y_win / 4;
	return (e);
}

int		main(int ac, char **av)
{
	t_env	e;
	int		fd;

	if (ac == 1)
	{
		ft_putstr_fd("fdf: No arguments\n", 2);
		return (0);
	}
	if ((fd = open(av[1], O_RDWR)) == -1)
	{
		ft_putstr_fd("fdf: ", 2);
		perror(av[1]);
		exit(EXIT_FAILURE);
	}
	e = map_to_str(fd, e);
	e = init_e(ac, av, e);
	e = compute_map(e);
	fdf(e);
	return (0);
}
