/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scandir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 08:40:29 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/20 18:52:28 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dirlist	*scan_directory(char *path, t_options ops)
{
	DIR				*dir;
	struct dirent	*dp;
	t_dirlist		*list;

	dir = get_dir(path);
	list = (void *)0;
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

DIR			*get_dir(char *path)
{
	DIR		*ret;
	char	*full_path;

	if (path[0] == '/' || path[0] == '.')
		ret = opendir(path);
	else
	{
		ret = opendir((full_path = ft_strjoin("./", path)));
		ft_strdel(&full_path);
	}
	if (ret == NULL)
	{
		write(2, "invalid filename or path: ", 26);
		write(1, path, ft_strlen(path));
		write(1, "\n", 1);
		exit(1);
	}
	return (ret);
}

int			is_dir(char *path)
{
	struct stat f_stat;

	if (stat(path, &f_stat) < 0)
		return (0);
	return (S_ISDIR(f_stat.st_mode));
}
