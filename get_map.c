/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/14 11:40:41 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/14 16:23:28 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		*malloc_me(size_t size)
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

t_linelist	*get_map(char *file_name)
{
	t_linelist	*begin_list;
	t_linelist	*map;
	char		*line;
	int			fd;

	map = l_lstnew(NULL);
	begin_list = map;
	if ((fd = open(file_name, O_RDONLY)) == -1)
	{
		perror("open:");
		exit(EXIT_FAILURE);
	}
	while (get_next_line(fd, &line) == 1)
	{
		l_lst_creat_after(map, line);
		map = map->next;
	}
	return (begin_list);
}

int			main(int argc, char **argv)
{
	t_linelist	*map;

	(void)argc;
	map = get_map(argv[1]);
	while (map)
	{
		ft_putendl(map->line);
		map = map->next;
	}
	return (0);
}