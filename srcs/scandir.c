/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scandir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 08:40:29 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/21 19:37:52 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dirlist	*scan_directory(char *path, t_options ops)
{
	DIR				*dir;
	struct dirent	*dp;
	t_dirlist		*list;

	list = (void *)0;
	if (!(dir = get_dir(path)))
		return (list);
	while ((dp = readdir(dir)) != NULL)
		if (*dp->d_name && (dp->d_name[0] != '.' || ops.a))
			push_list(&list, create_list_item(dp, path));
	if (ops.t)
		sort_list(&list, &cmp_time_modified, ops);
	else
		sort_list(&list, &cmp_filename, ops);
	closedir(dir);
	return (list);
}

static void	print_error(char *path)
{
	if (1/*is_readonly(path)*/)
	{
		write(1, "ft_ls: ", 7);
		write(1, path, ft_strlen(path));
		write(1, ": Permission denied\n", 20);
	}
}

static char	*get_d_name(char *path)
{
	char	*next;

	if (!(next = ft_strchr(path, '/')))
		return (path);
	else
		return (get_d_name(next + 1));
}

DIR			*get_dir(char *path)
{
	DIR		*ret;
	char	*full_path;

	full_path = (void *)0;
	if (path[0] == '/' || path[0] == '.')
		ret = opendir(path);
	else
		ret = opendir((full_path = ft_strjoin("./", path)));
	if (!ret)
		print_error(get_d_name(path));
	if (full_path != (void *)0)
		ft_strdel(&full_path);
	return (ret);
}

int			is_dir(char *path)
{
	struct stat f_stat;

	if (stat(path, &f_stat) < 0)
		return (0);
	return (S_ISDIR(f_stat.st_mode));
}
