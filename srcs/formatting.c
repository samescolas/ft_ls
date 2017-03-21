/* ************************************************************************** */ /*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 11:56:45 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/20 18:32:40 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_lengths	*init_max_lengths()
{
	t_lengths	*ret;

	ret = (t_lengths *)malloc(sizeof(t_lengths));
	if (ret)
	{
		ret->num_links = 0;
		ret->pwd = 0;
		ret->grp = 0;
		ret->f_size = 0;
		ret->total = 0;
	}
	return (ret);
}

t_lengths	*get_max_lengths(t_dirlist *list)
{
	struct stat		f_stat;
	struct passwd	*pwd;
	struct group	*grp;
	t_lengths		*maxes;
	char			*path;

	maxes = init_max_lengths();
	while (list)
	{
		path = ft_strjoin(list->path, list->dir->d_name);
		if (lstat(path, &f_stat) < 0)
			return (maxes);
		pwd = getpwuid(f_stat.st_uid);
		grp = getgrgid(f_stat.st_gid);
		if (f_stat.st_size > 0)
			maxes->total += (f_stat.st_size / 512);
		if (f_stat.st_size > 0 && f_stat.st_size % 512 != 0)
			maxes->total += 1;
		if (ft_numlen(f_stat.st_nlink) > maxes->num_links)
			maxes->num_links = ft_numlen(f_stat.st_nlink);
		if (ft_strlen(pwd->pw_name) > maxes->pwd)
			maxes->pwd = ft_strlen(pwd->pw_name);
		if (ft_strlen(grp->gr_name) > maxes->grp)
			maxes->grp = ft_strlen(grp->gr_name);
		if (ft_numlen(f_stat.st_size) > maxes->f_size)
			maxes->f_size = ft_numlen(f_stat.st_size);
		ft_strdel(&path);
		list = list->next;
	}
	return (maxes);
}
