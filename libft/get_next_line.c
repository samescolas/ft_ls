/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 13:45:10 by sescolas          #+#    #+#             */
/*   Updated: 2017/02/28 18:49:08 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_file	*create_file(int fd)
{
	t_file	*file;

	file = (t_file *)malloc(sizeof(t_file));
	if (file)
	{
		file->fd = fd;
		ft_bzero(file->buffer, BUFF_SIZE + 1);
		file->next = NULL;
	}
	return (file);
}

static t_file	*get_file(t_file **files, int fd)
{
	t_file	*file;

	if (!*files)
	{
		file = create_file(fd);
		*files = file;
	}
	else
	{
		file = *files;
		while (file->next && file->fd != fd)
			file = file->next;
		if (file->fd != fd)
		{
			file->next = create_file(fd);
			file = file->next;
		}
	}
	return (file);
}

static int		split_string(char **line, char *buffer, char c)
{
	char	*ret;
	char	*newline;

	ret = ft_strnew(ft_strlen(*line) + ft_strfind(buffer, c));
	ft_strcpy(ret, *line);
	free(*line);
	*line = ret;
	ft_strncat(*line, buffer, ft_strfind(buffer, c));
	if ((newline = ft_strchr(buffer, '\n')))
	{
		ft_memmove(buffer, newline + 1, ft_strlen(newline));
		ft_bzero(ft_strchr(buffer, '\0'), BUFF_SIZE - ft_strlen(buffer));
	}
	else
		ft_bzero(buffer, BUFF_SIZE);
	return (c == '\n');
}

int				get_next_line(const int fd, char **line)
{
	static t_file	*files = (void *)0;
	t_file			*file;
	int				ret;

	if (!line)
		return (-1);
	*line = ft_strdup("\0");
	file = get_file(&files, fd);
	if (*(file->buffer))
		if (split_string(\
			line, file->buffer, ft_strchr(file->buffer, '\n') ? '\n' : '\0'))
			return (1);
	while ((ret = read(file->fd, file->buffer, BUFF_SIZE)) > 0)
		if (split_string(\
			line, file->buffer, ft_strchr(file->buffer, '\n') ? '\n' : '\0'))
			return (1);
	if (ret > 0 || **line != '\0')
		return (1);
	else if (ret == 0)
		return (0);
	else
		return (-1);
}
