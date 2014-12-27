/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/16 14:49:02 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/17 10:30:00 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_nbrlen(long long nbr)
{
	size_t	length;

	length = 0;
	if (nbr == 0)
		length = 1;
	else
	{
		while (nbr != 0)
		{
			nbr /= 10;
			length++;
		}
	}
	return (length);
}
