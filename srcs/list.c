/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 08:25:35 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/17 12:25:22 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dirlist	*create_list_item(struct dirent *p_dir, char *path)
{
	t_dirlist	*ret;

	ret = (t_dirlist *)malloc(sizeof(t_dirlist));
	if (ret)
	{
		if (path[ft_strlen(path) - 1] == '/')
			ret->path = ft_strjoin(path, "");
		else
			ret->path = ft_strjoin(path, "/");
		ret->dir = (struct dirent *)malloc(sizeof(struct dirent));
		ft_memcpy(ret->dir, p_dir, sizeof(struct dirent));
		ret->next = NULL;
	}
	return (ret);
}

void		free_node(t_dirlist *node)
{
	if (!node)
		return ;
	ft_strdel(&(node->path));
	free(node->dir);
	node->next = NULL;
	node->dir = NULL;
}

void		free_list(t_dirlist **list)
{
	t_dirlist	*tmp;

	if (!list || !*list)
		return ;
	tmp = *list;
	*list = (*list)->next;
	free_node(tmp);
}

void		push_list(t_dirlist **list, t_dirlist *node)
{
	t_dirlist	*tmp;

	tmp = *list;
	if (!node)
		return ;
	if (!list || !*list)
	{
		*list = node;
		node->next = NULL;
	}
	else
	{
		node->next = tmp;
		*list = node;
	}
}

t_dirlist	*pop_list(t_dirlist **list)
{
	t_dirlist	*tmp;

	if (!list || !*list)
		return ((void *)0);
	tmp = *list;
	*list = (*list)->next;
	return (tmp);
}

void		swap_nodes(t_dirlist **list, t_dirlist *n1, t_dirlist *n2)
{
	t_dirlist	*tmp1;
	t_dirlist	*tmp2;

	tmp1 = *list;
	tmp2 = n2->next;
	if (tmp1 == n1)
		*list = n2;
	else
	{
		while (tmp1->next != n1)
			tmp1 = tmp1->next;
		tmp1->next = n2;
		tmp1 = n1;
	}
	while (tmp1->next != n2)
		tmp1 = tmp1->next;
	tmp1->next = n1;
	n2->next = n1->next;
	n1->next = tmp2;
}

void		sort_list(t_dirlist **list, int (*f_cmp)(const char *, const char *), t_options op)
{
	t_dirlist	*min;
	t_dirlist	*node;
	t_dirlist	*tmp;
	int			cmp;

	node = *list;
	while (node)
	{
		tmp = node->next;
		min = node;
		while (tmp)
		{
			cmp = f_cmp((const char *)tmp->dir->d_name, (const char *)min->dir->d_name);
			cmp = (op.r ? cmp * -1 : cmp);
			if (cmp < 0)
				min = tmp;
			tmp = tmp->next;
		}
		if (node != min)
		{
			swap_nodes(list, node, min);
			node = min->next;
		}
		else
			node = node->next;
	}
}
