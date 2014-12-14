/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabstrlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/22 11:35:58 by ncolliau          #+#    #+#             */
/*   Updated: 2014/11/22 11:46:36 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_tabstrlen(char **tabstr)
{
	int		i;

	if (tabstr == NULL)
		return (0);
	i = 0;
	while (tabstr[i])
		i++;
	return (i);
}