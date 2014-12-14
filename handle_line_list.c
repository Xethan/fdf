/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/23 11:09:53 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/14 15:02:38 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		l_lstadd(t_linelist **begin_list, t_linelist *new)
{
	new->next = *begin_list;
	*begin_list = new;
}

t_linelist	*l_lstnew(char *line)
{
	t_linelist	*new_list;

	new_list = (t_linelist *)malloc_me(sizeof(t_linelist));
	new_list->line = (char *)malloc_me((ft_strlen(line) + 1) * sizeof(char));
	if (line == NULL)
		new_list->line = NULL;
	else
		ft_memmove(new_list->line, line, ft_strlen(line) + 1);
	new_list->next = NULL;
	return (new_list);
}

void		l_lst_creat_after(t_linelist *list, char *line)
{
	t_linelist	*new;

	new = l_lstnew(line);
	new->next = list->next;
	list->next = new;
}

void		l_lstdel(t_linelist **begin_list)
{
	t_linelist	*p_list;
	t_linelist	*cpy;

	p_list = *begin_list;
	while (p_list)
	{
		free(p_list->line);
		cpy = p_list;
		p_list = p_list->next;
		free(cpy);
	}
}

void		l_lst_creat_begin(t_linelist **begin_list, char *line)
{
	t_linelist	*new;

	new = l_lstnew(line);
	l_lstadd(begin_list, new);
}
