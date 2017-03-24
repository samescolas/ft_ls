/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 09:53:29 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/23 18:14:47 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_path(char *path)
{
	static int	first_call;

	if (first_call == 424242)
		write(1, "\n", 1);
	else
		first_call = 424242;
	if (ft_strlen(get_d_name(path)) == 0)
		write(1, path, ft_strlen(path));
	else
		write(1, get_d_name(path), ft_strlen(get_d_name(path)));
	write(1, ":\n", 2);
}

static void	recurse(t_btree *node, t_options ops, t_lengths *empty)
{
	char	*full_path;

	full_path = ft_strjoin(node->path, node->dir->d_name);
	if (ft_strcmp(node->dir->d_name, ".") && ft_strcmp(node->dir->d_name, "..") &&
			is_dir(full_path))
	{
		write(1, "\n", 2);
		ft_ls(full_path, ops, FALSE);
		if (node->left || node->right)
			write(1, "\n", 1);
	}
	ft_strdel(&full_path);
}

void	ft_ls(char *path, t_options ops, t_bool one_and_only)
{
	t_btree			*tree;
	char			*full_path;

	tree = (void *)0;
	if (path[0] != '.' && path[0] != '/')
		full_path = ft_strjoin("./", path);
	else
		full_path = ft_strdup(path);
	if (!one_and_only)
		print_path(full_path);
	tree = scan_directory(full_path, ops);
	print_tree(tree, ops);
	if (ops.R)
		btree_apply_infix(tree, ops, (void *)0, &recurse);
	ft_strdel(&full_path);
}

static void	call_ls(t_btree *node, t_options ops, t_lengths *empty)
{
	t_lengths	*maxes;
	if (is_dir(node->path))
		ft_ls(node->path, ops, !ops.multiple_files);
	else if (ops.l || ops.g)
	{
		maxes = get_max_lengths(node, ops);
		print_long(node->path, ops, *maxes);
		pad_str(node->path, 0, (ops.G ? BLU : (void *)0));
		write(1, "\n", 1);
		ft_bzero(maxes, sizeof(maxes));
		free(maxes);
	}
	else
	{
		write(1, node->path, ft_strlen(node->path));
		write(1, "\n", 1);
	}
}

static t_btree	*parse_args(char **argv, int argc, t_options ops)
{
	int			i;
	char		*path;
	struct stat	f_stat;
	t_btree		*tree;
	t_btree		*node;

	i = -1;
	tree = (void *)0;
	while (++i < argc)
	{
		node = create_listnode(argv[i]);
		if (argv[i][0] != '.' && argv[i][0] != '/')
			path = ft_strjoin("./", argv[i]);
		else
			path = ft_strdup(argv[i]);
		if (stat(path, &f_stat) >= 0)
		{
			ft_strdel(&path);
			btree_insert(&tree, node, ops, (ops.t ? &cmp_args_t : &cmp_args_f));
		}
		else
		{
			ft_strdel(&path);
			path = get_d_name(argv[i]);
			write(1, "ft_ls: ", 7);
			write(1, path, ft_strlen(path));
			write(1, ": No such file or directory\n", 28);
		}
	}
	return (tree);
}

int		main(int argc, char **argv)
{
	DIR				*dp;
	t_options		*ops;
	int				i;
	t_btree			*tree;

	i = 0;
	tree = (void *)0;
	ops = init_options();
	while (++i < argc && argv[i][0] == '-')
		add_options(argv[i], ops);
	if (i < argc)
		tree = parse_args(&(argv[i]), argc - i, *ops);
	else
		ft_ls(".", *ops, TRUE);
	ops->multiple_files = (argc - i > 1);
	btree_apply_infix(tree, *ops, (void *)0, &call_ls);
	return (0);
}
