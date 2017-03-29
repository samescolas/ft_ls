/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 15:28:24 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/24 17:49:07 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_lengths	*init_max_lengths(void)
{
	t_lengths	*ret;

	ret = (t_lengths *)malloc(sizeof(t_lengths));
	if (ret)
	{
		ret->num_links = 0;
		ret->pwd = 0;
		ret->grp = 0;
		ret->f_size = 0;
		ret->minor = 0;
		ret->major = 0;
		ret->total = 0;
	}
	return (ret);
}

void			add_to_maxes(t_btree *node, t_ops ops, t_lengths *maxes)
{
	struct stat		f_stat;
	struct passwd	*pwd;
	struct group	*grp;
	size_t			val;

	if (ops.one)
		write(1, "", 1);
	f_stat = get_stat(node->path, (node->dir ? node->dir->d_name : ""));
	if (S_ISBLK(f_stat.st_mode) || S_ISCHR(f_stat.st_mode))
		if ((val = ft_numlen(major(f_stat.st_rdev))) > maxes->major)
			maxes->major = val;
	if (S_ISBLK(f_stat.st_mode) || S_ISCHR(f_stat.st_mode))
		if ((val = ft_numlen(minor(f_stat.st_rdev))) > maxes->minor)
			maxes->minor = val;
	pwd = getpwuid(f_stat.st_uid);
	grp = getgrgid(f_stat.st_gid);
	maxes->total += f_stat.st_blocks;
	if ((val = ft_numlen(f_stat.st_nlink)) > maxes->num_links)
		maxes->num_links = val;
	if ((val = ft_strlen(pwd->pw_name)) > maxes->pwd)
		maxes->pwd = val;
	if ((val = ft_strlen(grp->gr_name)) > maxes->grp)
		maxes->grp = val;
	if ((val = ft_numlen(f_stat.st_size)) > maxes->f_size)
		maxes->f_size = val;
}

void				pad_str(char *str, int offset, char *color)
{
	while (offset++ < 0)
		write(1, " ", 1);
	--offset;
	if (color)
		write(1, color, ft_strlen(color));
	write(1, str, ft_strlen(str));
	while (offset-- > 0)
		write(1, " ", 1);
	if (color != (void *)0)
		write(1, DEF, 4);
}

void				pad_num(int num, int offset, char *color)
{
	while (offset++ < 0)
		write(1, " ", 1);
	--offset;
	if (color)
		write(1, color, ft_strlen(color));
	ft_putnbr(num);
	while (offset-- > 0)
		write(1, " ", 1);
	if (color != (void *)0)
		write(1, DEF, 4);
}

t_lengths			*get_max_lengths(t_btree *tree, t_ops ops)
{
	t_lengths		*maxes;

	maxes = init_max_lengths();
	btree_apply_infix(tree, ops, maxes, &add_to_maxes);
	return (maxes);
}
