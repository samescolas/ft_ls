/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 19:26:07 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/24 19:52:29 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	btree_apply_suffix(t_btree *tree, void (*applyf)(t_btree *))
{
	if (!tree)
		return ;
	btree_apply_suffix(tree->left, applyf);
	btree_apply_suffix(tree->right, applyf);
	applyf(tree);
}

void		free_node(t_btree *node)
{
	node->left = (void *)0;
	node->right = (void *)0;
	ft_strdel(&(node->path));
	free(node);
	node = (void *)0;
}

void		uproot(t_btree **tree)
{
	btree_apply_suffix(*tree, &free_node);
	*tree = (void *)0;
}
