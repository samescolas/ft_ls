/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 17:10:51 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/24 19:47:54 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_btree	*load_error_message(t_btree *node, t_ops ops)
{
	static t_btree	*error_tree;

	if (!error_tree)
		error_tree = (void *)0;
	if (!node)
		return (error_tree);
	btree_insert(&error_tree, node, ops, &cmp_filename);
	return (error_tree);
}

static void		print_node(t_btree *node, t_ops ops, t_lengths *empty)
{
	if (empty)
		empty = (void *)0;
	ft_padstr("ft_ls: ", 0, ops.color ? RED : (void *)0);
	ft_padstr(node->path, 0, ops.color ? RED : (void *)0);
	ft_padstr(": No such file or directory\n", 0, ops.color ? RED : (void *)0);
}

static void		print_error_messages(t_ops ops)
{
	t_btree	*tmp;

	tmp = load_error_message((void *)0, ops);
	btree_apply_infix(tmp, ops, (void *)0, &print_node);
	uproot(&tmp);
}

t_btree			*parse_args(char **argv, int argc, t_ops ops)
{
	int			i;
	struct stat	f_stat;
	char		*path;
	t_btree		*tree;
	t_btree		*node;

	i = -1;
	tree = (void *)0;
	while (++i < argc)
	{
		node = create_arg_node(argv[i]);
		if (argv[i][0] != '.' && argv[i][0] != '/')
			path = ft_strjoin("./", argv[i]);
		else
			path = ft_strdup(argv[i]);
		if (stat(path, &f_stat) >= 0)
			btree_insert(&tree, node, ops, (ops.t ? &cmp_args_t : &cmp_args_f));
		else
			load_error_message(node, ops);
		ft_strdel(&path);
	}
	print_error_messages(ops);
	return (tree);
}
