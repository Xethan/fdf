/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 15:38:56 by ncolliau          #+#    #+#             */
/*   Updated: 2014/11/22 10:54:26 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if ((ptr = ft_strdup(s2)) == NULL)
		return (NULL);
	while (s1[j])
		j++;
	while (ptr[i])
	{
		s1[j + i] = ptr[i];
		i++;
	}
	s1[j + i] = '\0';
	free(ptr);
	return (s1);
}
