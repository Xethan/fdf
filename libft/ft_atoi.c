/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 14:57:01 by ncolliau          #+#    #+#             */
/*   Updated: 2014/11/13 12:48:48 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_atoi(const char *str)
{
	int i;
	int num;
	int signe;

	i = 0;
	num = 0;
	signe = 1;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		signe = (str[i] - 44) * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	num *= signe;
	return (num);
}
