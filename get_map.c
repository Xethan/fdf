/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/14 11:40:41 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/27 15:27:19 by ncolliau         ###   ########.fr       */
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

t_env	get_map(char *file_name)
{
	t_env	e;
	char	*line;
	int		fd;
	int		i;

	e.x = 0;
	e.y = 0;
	line = NULL;
	e.map = (t_point **)malloc_me(100 * sizeof(t_point *));
	if ((fd = open(file_name, O_RDONLY)) == -1)
	{
		perror("open:");
		exit(EXIT_FAILURE);
	}
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
			e.map[e.y][e.x].x = 50 + e.map[e.y][e.x].z + e.x * 20;
			e.map[e.y][e.x].y = 50 - e.map[e.y][e.x].z + e.y * 20;
			i += ft_nbrlen(e.map[e.y][e.x].z);
			e.x++;
		}
		free(line);
		e.y++;
	}
	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, 800, 800, "fdf 42");
	return (e);
}

int		main(int argc, char **argv)
{
	t_env	e;

	(void)argc;
	e = get_map(argv[1]);
	fdf(e);
	return (0);
}
