/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/10 09:43:30 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/14 16:19:20 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft.h"
# include "get_next_line.h"

typedef struct			s_fdf
{
	void				*mlx;
	void				*win;
}						t_fdf;

typedef struct			s_linelist
{
	char				*line;
	struct s_linelist	*next;
}						t_linelist;

t_linelist				*get_map(char *file_name);
void					*malloc_me(size_t size);

int						get_next_line(int const fd, char **line);

void					l_lstadd(t_linelist **begin_list, t_linelist *new);
t_linelist				*l_lstnew(char *line);
void					l_lst_creat_after(t_linelist *list, char *line);
void					l_lstdel(t_linelist **begin_list);

#endif