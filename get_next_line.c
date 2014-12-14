/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 14:37:40 by ncolliau          #+#    #+#             */
/*   Updated: 2014/11/26 15:01:47 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		line_len(char *buf)
{
	int		line_len;

	line_len = 0;
	while (buf[line_len] != '\n' && buf[line_len] != '\0')
		line_len++;
	return (line_len);
}

char	*my_read(int fd)
{
	int		read_bytes;
	char	*buf;
	char	*cpy;
	char	buffer[BUFF_SIZE + 1];

	read_bytes = 1;
	if ((buf = (char *)malloc(1 * sizeof(char))) == NULL)
		return (NULL);
	while (read_bytes != 0)
	{
		if ((read_bytes = read(fd, buffer, BUFF_SIZE)) == -1)
			return (NULL);
		buffer[read_bytes] = '\0';
		cpy = buf;
		if ((buf = ft_strjoin(buf, buffer)) == NULL)
			return (NULL);
		free(cpy);
		ft_memset(buffer, 0, read_bytes);
	}
	return (buf);
}

int		get_next_line(int const fd, char **line)
{
	static char	*buf;

	if (BUFF_SIZE > MAX_SIZE_BUFFER || BUFF_SIZE <= 0)
		return (-1);
	if (!buf)
		if ((buf = my_read(fd)) == NULL)
			return (-1);
	if ((*line = ft_strsub(buf, 0, line_len(buf))) == NULL)
		return (-1);
	buf += line_len(buf);
	if (*buf == '\0')
		return (0);
	buf++;
	return (1);
}
