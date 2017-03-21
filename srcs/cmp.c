/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 09:09:56 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/20 18:10:52 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static struct stat	get_stat(char *path, char *name)
{
	char		*full_path;
	struct stat	ret;

	full_path = ft_strjoin(path, name);
	if (lstat(full_path, &ret) < 0)
		return (ret);
	ft_strdel(&full_path);
	return (ret);
}

int		cmp_time_modified(t_dirlist *f1, t_dirlist *f2)
{
	struct stat		f1_stat;
	struct stat		f2_stat;
	struct timespec	t1;
	struct timespec	t2;

	f1_stat = get_stat(f1->path, f1->dir->d_name);
	f2_stat = get_stat(f2->path, f2->dir->d_name);
	t1 = f1_stat.st_mtimespec;
	t2 = f2_stat.st_mtimespec;
	if (f1_stat.st_mtime == f2_stat.st_mtime)
	{
		if (t1.tv_nsec == t2.tv_nsec)
			return (ft_strcmp(f2->dir->d_name, f1->dir->d_name));
		else
			return (t2.tv_nsec - t1.tv_nsec);
	}
	else
		return (f2_stat.st_mtime - f1_stat.st_mtime);
}

int		cmp_filename(t_dirlist *f1, t_dirlist *f2)
{
	return (ft_strcmp(f1->dir->d_name, f2->dir->d_name));
}
