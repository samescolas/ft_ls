/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 19:47:13 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/24 17:47:42 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_long(char *path, t_ops ops, t_lengths maxes)
{
	struct stat	f_stat;

	if (lstat(path, &f_stat) < 0)
		return ;
	print_file_mode(f_stat, ops.color);
	print_file_permissions(f_stat, ops.color);
	print_num_links(f_stat, maxes.num_links, ops.color);
	print_group_info(f_stat, ops, maxes, ops.color);
	print_file_size(f_stat, maxes, ops.color);
	print_time(f_stat, ops.color);
}

static void	print_filename(char *path, char *filename, t_ops ops)
{
	if (is_dir(path))
		pad_str(filename, 0, (ops.color ? BL2 : (void *)0));
	else
		pad_str(filename, 0, (ops.color ? BLU : (void *)0));
}

static void	print_linked_to_file(char *filepath, t_ops ops)
{
	struct stat	f_stat;
	char		buf[MAX_PATH];

	if (lstat(filepath, &f_stat) < 0)
		return ;
	if (!S_ISLNK(f_stat.st_mode))
	{
		write(1, "\n", 1);
		return ;
	}
	pad_str(" -> ", 0, (ops.color ? MAG : (void *)0));
	ft_bzero(buf, MAX_PATH);
	if (readlink(filepath, (char *)&buf, MAX_PATH) > 0)
		pad_str(buf, 0, (ops.color ? MAG : (void *)0));
	write(1, "\n", 1);
}

static void	print_node(t_btree *node, t_ops ops, t_lengths *maxes)
{
	char	*full_path;

	full_path = (void *)0;
	if ((node->path)[0] == '.')
		full_path = ft_strjoin(node->path, node->dir->d_name);
	else if ((node->path)[0] == '/')
		full_path = ft_strjoin(node->path, node->dir->d_name);
	else
		full_path = ft_strjoin("", node->dir->d_name);
	if (ops.l || ops.g)
		print_long(full_path, ops, *maxes);
	print_filename(full_path, node->dir->d_name, ops);
	if (ops.l || ops.g)
		print_linked_to_file(full_path, ops);
	else
		write(1, "\n", 1);
	ft_strdel(&full_path);
}

void		print_tree(t_btree *tree, t_ops ops, t_lengths maxes)
{
	char		*full_path;

	if (!tree)
		return ;
	if (ops.l || ops.g)
	{
		write(1, "total ", 6);
		ft_putnbr(maxes.total);
		write(1, "\n", 1);
	}
	btree_apply_infix(tree, ops, &maxes, &print_node);
}
