/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scandir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 08:40:29 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/13 11:36:48 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dirlist	*scan_directory(DIR *dir, t_options ops)
{
	struct dirent	*dp;
	t_dirlist		*list;

	if ((dp = readdir(dir)) != NULL)
		list = create_list_item(dp);
	while ((dp = readdir(dir)) != NULL)
		if (dp->d_name[0] != '.' || ops.a)
			push_list(&list, create_list_item(dp));
	if (ops.t)
		sort_list(&list, &cmp_time_modified, ops);
	else
		sort_list(&list, &ft_strcmp, ops);
	return (list);
}

DIR			*get_dir(char *path)
{
	DIR	*ret;

	if (path[0] == '/')
		ret = opendir(path);
	else
		ret = opendir(ft_strjoin("./", path));
	if (ret == NULL)
	{
		write(2, "invalid filename or path\n", 25);
		exit(1);
	}
	return (ret);
}

int			is_dir(char *path)
{
	struct stat f_stat;

	if (path[0] == '.')
	{
		if (stat(path, &f_stat) < 0)
			return (0);
	}
	else
	{
		if (stat(path, &f_stat) < 0)
			return (0);
	}
	return (S_ISDIR(f_stat.st_mode));
}
