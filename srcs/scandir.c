/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scandir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 08:40:29 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/23 14:36:45 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_error(char *path)
{
	if (1/*is_readonly(path)*/)
	{
		write(1, "ft_ls: ", 7);
		write(1, path, ft_strlen(path));
		write(1, ": Permission denied\n", 20);
	}
}

char	*get_d_name(char *path)
{
	char	*next;

	if (!(next = ft_strchr(path, '/')))
		return (path);
	else
		return (get_d_name(next + 1));
}

static DIR	*get_dir(char *path)
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

t_btree	*scan_directory(char *path, t_options ops)
{
	DIR				*dir;
	struct dirent	*dp;
	t_btree			*tree;

	tree = (void *)0;
	if (!(dir = get_dir(path)))
		return (tree);
	while ((dp = readdir(dir)) != NULL)
		if (*dp->d_name && (dp->d_name[0] != '.' || ops.a))
			btree_insert(&tree, create_node(dp, path), ops, ops.t ? &cmp_time: &cmp_filename);
	closedir(dir);
	return (tree);
}

int			is_dir(char *path)
{
	struct stat f_stat;

	if (stat(path, &f_stat) < 0)
		return (0);
	return (S_ISDIR(f_stat.st_mode));
}
