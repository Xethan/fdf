/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlonglong.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/16 14:33:04 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/17 11:15:31 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putlonglong(long long nbr)
{
	if (nbr < 0)
	{
		nbr *= -1;
		ft_putchar('-');
	}
	if (nbr >= 10)
	{
		ft_putlonglong(nbr / 10);
		ft_putchar('0' + (nbr % 10));
	}
	else
		ft_putchar('0' + nbr);
}
