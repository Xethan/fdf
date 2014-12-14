/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/10 09:43:30 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/14 11:59:36 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"
# include "get_next_line.h"

typedef struct	s_fdf
{
	void		*mlx;
	void		*win;
}				t_fdf;


char			**get_map(char *file_name);

#endif