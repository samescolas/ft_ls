/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scandir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 08:40:29 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/24 19:04:32 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_error(char *path, t_bool color)
{
	ft_padstr("ft_ls: ", 0, color ? RED : (void *)0);
	ft_padstr(path, 0, color ? RED : (void *)0);
	ft_padstr(": Permission denied\n", 0, color ? RED : (void *)0);
}

static DIR	*get_dir(char *path, t_bool color)
{
	DIR		*ret;
	char	*full_path;

	full_path = (void *)0;
	if (path[0] == '/' || path[0] == '.')
		ret = opendir(path);
	else
	{
		full_path = ft_strjoin("./", path);
		ret = opendir(full_path);
	}
	if (!ret && is_dir(path))
		print_error(get_d_name(path), color);
	if (full_path != (void *)0)
		ft_strdel(&full_path);
	return (ret);
}

char		*get_d_name(char *path)
{
	return (ft_strrchr(path, '/'));
}

int			is_dir(char *path)
{
	struct stat f_stat;

	if (stat(path, &f_stat) < 0)
		return (0);
	return (S_ISDIR(f_stat.st_mode));
}

t_btree		*scan_directory(char *path, t_ops ops, t_lengths *maxes)
{
	DIR				*dir;
	struct dirent	*dp;
	t_btree			*tree;
	t_btree			*node;

	tree = (void *)0;
	if (!(dir = get_dir(path, ops.color)))
		return (tree);
	while ((dp = readdir(dir)) != NULL)
	{
		node = create_node(dp, path);
		if ((dp->d_name[0] != '.' || ops.a))
		{
			btree_insert(&tree, node, ops,\
					ops.t ? &cmp_time : &cmp_filename);
			add_to_maxes(node, ops, maxes);
		}
		else
			free_node(node);
	}
	closedir(dir);
	return (tree);
}
