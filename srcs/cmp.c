/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 09:09:56 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/24 17:44:28 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

struct stat	get_lstat(char *path)
{
	struct stat	ret;

	if (lstat(path, &ret) < 0)
		return (ret);
	return (ret);
}

int			cmp_filename(t_btree *f1, t_btree *f2)
{
	return (ft_strcmp(f1->d_name, f2->d_name));
}

int			cmp_time(t_btree *f1, t_btree *f2)
{
	struct stat		f1_stat;
	struct stat		f2_stat;
	struct timespec	t1;
	struct timespec	t2;

	f1_stat = get_lstat(f1->path);
	f2_stat = get_lstat(f2->path);
	t1 = f1_stat.st_mtimespec;
	t2 = f2_stat.st_mtimespec;
	if (f1_stat.st_mtime == f2_stat.st_mtime)
	{
		if (t1.tv_nsec == t2.tv_nsec)
			return (cmp_filename(f1, f2));
		else
			return (t2.tv_nsec - t1.tv_nsec);
	}
	else
		return (f2_stat.st_mtime - f1_stat.st_mtime);
}

int			cmp_args_f(t_btree *f1, t_btree *f2)
{
	if (is_dir(f1->path))
	{
		if (is_dir(f2->path))
			return (ft_strcmp(f1->path, f2->path));
		else
			return (1);
	}
	else
	{
		if (is_dir(f2->path))
			return (ft_strcmp(f1->path, f2->path));
		else
			return (-1);
	}
}

int			cmp_args_t(t_btree *f1, t_btree *f2)
{
	if (is_dir(f1->path))
	{
		if (is_dir(f2->path))
			return (cmp_time(f1, f2));
		else
			return (1);
	}
	else
	{
		if (is_dir(f2->path))
			return (cmp_time(f1, f2));
		else
			return (-1);
	}
}
