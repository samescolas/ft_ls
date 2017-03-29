/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
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
	char	*full_path;

	full_path = ft_strjoin(node->path, node->dir->d_name);
	if (ft_strcmp(node->dir->d_name, ".") && 	\
			ft_strcmp(node->dir->d_name, "..") &&
			is_dir(full_path) && !empty)
	{
		write(1, "\n", 1);
		ft_ls(full_path, ops, FALSE);
	}
	ft_strdel(&full_path);
}

static void		call_ls(t_btree *node, t_ops ops, t_lengths *empty)
{
	static int	first_func_call;
	t_lengths	*maxes;

	if (is_dir(node->path))
	{
		if (ops.multiple_files && first_func_call== 424242)
			write(1, "\n", 1);
		if (ops.multiple_files || empty)
			print_path(node->path);
		ft_ls(node->path, ops, TRUE);
	}
	else if (ops.l || ops.g)
	{
		maxes = get_max_lengths(node, ops);
		print_long(node->path, ops, *maxes);
		pad_str(node->path, 0, (ops.color ? BLU : (void *)0));
		write(1, "\n", 1);
		ft_bzero(maxes, sizeof(t_lengths));
		free(maxes);
	}
	else
	{
		write(1, node->path, ft_strlen(node->path));
		write(1, "\n", 1);
	}
	first_func_call = 424242;
}

void			ft_ls(char *path, t_ops ops, t_bool one_and_only)
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

int				main(int argc, char **argv)
{
	t_btree	*args;
	t_ops	*ops;
	int		i;

	args = (void *)0;
	ops = init_ops();
	i = 0;
	while (++i < argc && argv[i][0] == '-')
		add_options(argv[i], ops);
	if (i < argc)
		args = parse_args(&(argv[i]), argc - i, *ops);
	else
		ft_ls(".", *ops, TRUE);
	ops->multiple_files = (argc - i > 1);
	if (args)
	{
		btree_apply_infix(args, *ops, (void *)0, &call_ls);
		uproot(&args);
	}
	ft_bzero(ops, sizeof(t_ops));
	free(ops);
	return (0);
}
