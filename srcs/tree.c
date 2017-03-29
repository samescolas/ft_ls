/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 12:58:17 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/24 19:52:30 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_btree		*create_listnode(char *path)
{
	t_btree	*ret;

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
				ret->path = ft_strdup(path);
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

static int	compare(\
		t_btree *n1, t_btree *n2, t_ops ops, int (*cmp)(t_btree *, t_btree *))
{
	int		ret;

	if (ops.f)
		return (0);
	if ((ret = ((ops.r ? -1 : 1) * cmp(n1, n2))))
		return (ret);
	if (n1->dir && n2->dir)
		ret = (ops.r ? -1 : 1) * ft_strcmp(n1->dir->d_name, n2->dir->d_name);
	else
		ret = (ops.r ? -1 : 1) * ft_strcmp(n1->path, n2->path);
	return (ret);
}

void		btree_insert(t_btree **root, t_btree *node,\
		t_ops ops, int (*cmp)(t_btree *, t_btree *))
{
	t_btree	*tree;
	int		val;

	if (!(tree = *root))
		*root = node;
	else
	{
		val = compare(node, tree, ops, cmp);
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

void		btree_apply_infix(t_btree *root, t_ops ops,\
		t_lengths *maxes, void (*applyf)(t_btree *, t_ops, t_lengths *))
{
	if (!root)
		return ;
	btree_apply_infix(root->left, ops, maxes, applyf);
	applyf(root, ops, maxes);
	btree_apply_infix(root->right, ops, maxes, applyf);
}
