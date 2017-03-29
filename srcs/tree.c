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

t_btree		*create_arg_node(char *path)
{
	t_btree	*ret;

	ret = (t_btree *)malloc(sizeof(t_btree));
	if (ret)
	{
		ret->path = ft_strdup(path);
		ret->d_name = ret->path;
		ret->left = NULL;
		ret->right = NULL;
	}
	return (ret);
}

t_btree		*create_node(struct dirent *p_dir, char *path)
{
	t_btree	*ret;
	int		path_len;

	if ((ret = (t_btree *)malloc(sizeof(t_btree))))
	{
		path_len = ft_strlen(path) + ft_strlen(p_dir->d_name);
		path_len += (path[0] != '.' && path[0] != '/' ? 2 : 0);
		if (path[ft_strlen(path) - 1] != '/')
			path_len += 1;
		ret->path = ft_strnew(path_len);
		if (path[0] != '.' && path[0] != '/')
			ft_strcpy(ret->path, "./");
		ft_strcat(ret->path, path);
		if (path[ft_strlen(path) - 1] != '/')
			ft_strcat(ret->path, "/");
		ret->d_name = ft_strchr(ret->path, '\0');
		ft_strcat(ret->path, p_dir->d_name);
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
	if ((ret = ((ops.r ? -1 : 1) * cmp(n1, n2))) != 0)
		return (ret);
	ret = (ops.r ? -1 : 1);
	ret *= ft_strcmp(n1->d_name, n2->d_name);
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
