/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 12:58:17 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/23 17:51:49 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_btree		*create_listnode(char *path)
{
	t_btree *ret;

	ret = (t_btree *)malloc(sizeof(t_btree));
	if (ret)
	{
		ret->path = ft_strdup(path);
		ret->dir = NULL;
		ret->left = NULL;
		ret->right = NULL;
	}
	return (ret);
}


t_btree		*create_node(struct dirent	*p_dir, char *path)
{
	t_btree	*ret;

	ret = (t_btree *)malloc(sizeof(t_btree));
	if (ret)
	{
		if (path)
		{
			if (path[ft_strlen(path) - 1] == '/')
				ret->path = ft_strjoin(path, "");
			else
				ret->path = ft_strjoin(path, "/");
		}
		ret->dir = (struct dirent *)malloc(sizeof(struct dirent));
		if (ret->dir)
			ft_memcpy(ret->dir, p_dir, sizeof(struct dirent));
		ret->left = NULL;
		ret->right = NULL;
	}
	return (ret);
}

void		btree_insert(t_btree **root, t_btree *node, t_options ops, int (*cmp)(t_btree *, t_btree *))
{
	t_btree	*tree;
	int		val;

	tree = *root;
	if (!tree)
		*root = node;
	else	
	{
		if ((val = ((ops.r ? -1 : 1) * cmp(node, tree))) == 0)
		{
			if (node->dir)
				val = (ops.r ? -1 : 1) * ft_strcmp(node->dir->d_name, tree->dir->d_name);
			else
				val = (ops.r ? -1 : 1) * ft_strcmp(node->path, tree->path);
		}
		if (val < 0)
		{
			if (tree->left)
				btree_insert(&(tree->left), node, ops, cmp);
			else
				tree->left = node;
		}
		else
		{
			if (tree->right)
				btree_insert(&(tree->right), node, ops, cmp); 
			else
				tree->right = node;
		}
	}
}

void		btree_apply_infix(t_btree *root, t_options ops, t_lengths *maxes, void (*applyf)(t_btree *, t_options, t_lengths *))
{
	if (!root)
		return ;
	btree_apply_infix(root->left, ops, maxes, applyf);
	applyf(root, ops, maxes);
	btree_apply_infix(root->right, ops, maxes, applyf);
}
