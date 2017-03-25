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

static void	print_error_message(char *path)
{
	write(2, "ft_ls: ", 7);
	write(2, path, ft_strlen(path));
	write(2, ": No such file or directory\n", 28);
}

t_btree		*parse_args(char **argv, int argc, t_ops ops)
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
			btree_insert(&tree, node, ops, (ops.t ? &cmp_args_t : &cmp_args_f));
		else
			print_error_message(get_d_name(argv[i]));
		ft_strdel(&path);
	}
	return (tree);
}
