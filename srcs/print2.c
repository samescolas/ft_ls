/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 09:53:29 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/24 19:38:42 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		print_path(char *path)
{
	write(1, path, ft_strlen(path));
	write(1, ":\n", 2);
}

static void		recurse(t_btree *node, t_ops ops, t_lengths *empty)
{
	if (ft_strcmp(node->d_name, ".") && 	\
			ft_strcmp(node->d_name, "..") &&
			is_dir(node->path) && !empty)
	{
		write(1, "\n", 1);
		print_contents(node->path, ops, FALSE);
	}
}

void		display_file(t_btree *node, t_ops ops, t_lengths *maxes)
{
	static int	first_func_call;

	if (is_dir(node->path))
	{
		if (ops.multiple_files && first_func_call== 424242)
			write(1, "\n", 1);
		if (ops.multiple_files)
			print_path(node->path);
		print_contents(node->path, ops, TRUE);
	}
	else if (ops.l || ops.g)
	{
		print_long(node->path, ops, *maxes);
		ft_padstr(node->path, 0, (ops.color ? BLU : (void *)0));
		write(1, "\n", 1);
	}
	else
	{
		write(1, node->path, ft_strlen(node->path));
		write(1, "\n", 1);
	}
	first_func_call = 424242;
}

void			print_contents(char *path, t_ops ops, t_bool one_and_only)
{
	t_btree			*tree;
	t_lengths		*maxes;
	char			*full_path;

	tree = (void *)0;
	maxes = init_max_lengths();
	if (path[0] != '.' && path[0] != '/')
		full_path = ft_strjoin("./", path);
	else
		full_path = ft_strdup(path);
	if (!one_and_only)
		print_path(full_path);
	tree = scan_directory(full_path, ops, maxes);
	print_tree(tree, ops, *maxes);
	if (ops.recurse)
		btree_apply_infix(tree, ops, (void *)0, &recurse);
	ft_strdel(&full_path);
	ft_bzero(maxes, sizeof(t_lengths));
	free(maxes);
	uproot(&tree);
}
