/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/14 11:40:41 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/04 15:01:05 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	*malloc_me(size_t size)
{
	void	*content;

	content = malloc(size);
	if (content == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	return (content);
}

t_env	get_map(int fd, t_env e)
{
	char	*line;
	int		i;

	while (get_next_line(fd, &line) == 1)
	{
		e.x = 0;
		i = 0;
		e.map[e.y] = (t_point *)malloc_me(ft_strlen(line) * sizeof(t_point));
		while (line[i])
		{
			while (line[i] && !ft_isdigit(line[i]))
				i++;
			e.map[e.y][e.x].z = ft_atoi(line + i);
			e.map[e.y][e.x].x = e.x_mv + e.scale * 2 * (e.x - e.y);
			e.map[e.y][e.x].y = e.y_mv + e.scale * (e.x + (e.y - e.z_scale * e.map[e.y][e.x].z));
			i += ft_nbrlen(e.map[e.y][e.x].z);
			e.x++;
		}
		free(line);
		e.y++;
	}
	return (e);
}

int		main(int argc, char **argv)
{
	t_env	e;
	int		fd;

	e.x = 0;
	e.y = 0;
	e.x_mv = 350;
	e.y_mv = 50;
	e.scale = 15;
	e.z_scale = 0.5;
	e.map = (t_point **)malloc_me(100 * sizeof(t_point *));
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
	e = get_map(fd, e);
	fdf(e);
	return (0);
}
