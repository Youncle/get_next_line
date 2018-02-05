/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcarstoc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 16:33:48 by vcarstoc          #+#    #+#             */
/*   Updated: 2018/02/05 14:54:00 by vcarstoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static unsigned int check_line(char *buf)
{
	unsigned int i;

	i = 0;
	while (buf[i] != '\0')
	{
		if (buf[i] == '\n')
		{
			buf[i] = '\0';
			return(i + 1);
		}
		i++;
	}
	return (i);
}

static void			join_buf(char **buf2, char **buf1)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = NULL;
	tmp2 = NULL;
	if (*buf2 && **buf2)
	{
		tmp2 = ft_strdup(*buf2);
		if (*buf1)
		{
			tmp1 = ft_strdup(*buf1);
			free(*buf1);
		}
		*buf1 = ft_strjoin(tmp1, tmp2);
		if (tmp1)
			free(tmp1);
		if (tmp2)
			free(tmp2);
	}
}

static_int			return_line(char **buf, char **buf2, char **line)
{
	unsigned int	i;
	char			*tmp;

	tmp = NULL;
	i = check_line(*buf);
	*line = ft_strdup(*buf);
	tmp = ft_strdup(*buf + i);
	free(*buf);
	*buf = tmp;
	if (buf2)
		free(*buf2), *buf2 = NULL;
	return (1);
}

static int			get_next_line(const int fd, char **line)
{
	int			f;
	char		*buf2;
	static char	*buf = NULL;

	buf2 = NULL;
	if (fd <= 0 || (!(line)) || BUFF_SIZE < 1)
		return (-1);
	if ((!(buf2 = (char*)malloc(sizeof(char) * BUFF_SIZE + 1))))
		return (-1);
	while (((f = read(fd, buf2, BUFF_SIZE)) > 0) && (!(ft_strchr(buf2, '\n'))))
	{
		buf2[f] = '\0';
		join_buf(&buf2, &buf);
	}
	if (buf2 && *buf2 && f > 0)
	{
		buf2[f] = '\0';
		join_buf(&buf2, &buf);
	}
	if (f < 0)
		return (-1);
	if (buf && buf[0] != '\0')
		return (return_line(&buf, &buf2, line));
	if (buf2)
	{
		free(buf2);
		buf2 = NULL;
	}
	free(buf);
	buf = NULL;
	*line = NULL;
	return (0);
}
