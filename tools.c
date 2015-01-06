/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/06 13:59:14 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/06 14:22:03 by ncolliau         ###   ########.fr       */
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
	map = (char **)malloc_me((length + 2) * sizeof(char*));
	while (++i != length)
		map[i] = tmp[i];
	map[length + 1] = NULL;
	free(tmp);
	return (map);
}

t_env	get_coord(t_env e, int y, int x)
{
	if (e.iso == 1)
	{
		e.map[y][x].x = e.x_mv + e.scale * 2 * (x - y);
		e.map[y][x].y = e.y_mv + e.scale * (x + (y - e.z_scale * e.map[y][x].z));
	}
	else
	{
		e.map[y][x].x = e.x_mv - 300 + (14 * e.z_scale) * e.map[y][x].z + x * e.scale * 2;
		e.map[y][x].y = e.y_mv - (14 * e.z_scale) * e.map[y][x].z + y * e.scale * 2;
	}
	return (e);
}

t_env	compute_map(t_env e)
{
	int		x;
	int		y;
	
	x = 0;
	while (x != e.x)
	{
		y = 0;
		while (y != e.y)
		{
			e = get_coord(e, y, x);
			y++;
		}
		x++;
	}
	return (e);
}