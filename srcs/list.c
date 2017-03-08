/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 08:25:35 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/07 19:39:14 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dirlist		*create_list_item(struct dirent *p_dir)
{
	t_dirlist	*ret;

	ret = (t_dirlist *)malloc(sizeof(t_dirlist));
	if (ret)
	{
		ret->dir = p_dir;
		ret->next = NULL;
	}
	return (ret);
}

void		append_list(t_dirlist **list, t_dirlist *node)
{
	t_dirlist	*tmp;

	if (!*list)
		*list = node;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

void		push_list(t_dirlist **list, t_dirlist *node)
{
	if (!*list)
		*list = node;
	else
	{
		node->next = *list;
		*list = node;
	}
}

t_dirlist	*pop_list(t_dirlist **list)
{
	t_dirlist	*tmp;
	
	if (!*list)
		return ((void *)0);
	tmp = *list;
	*list = (*list)->next;
	return (tmp);
}

void		swap_nodes(t_dirlist **list, t_dirlist *n1, t_dirlist *n2)
{
	t_dirlist	*tmp1;
	t_dirlist	*tmp2;
/*
	write(1, "swapping ", 9);
	write(1, n1->dir->d_name, ft_strlen(n1->dir->d_name));
	write(1, " and ", 5);
	write(1, n2->dir->d_name, ft_strlen(n2->dir->d_name));
	write(1, "\n", 1);
*/
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

void		sort_list(t_dirlist **list, int (*f_cmp)(const char *, const char *))
{
	t_dirlist	*min;
	t_dirlist	*node;
	t_dirlist	*tmp;
	t_dirlist	*tmp2;

	node = *list;
	while (node)
	{
		tmp = node->next;
		min = node;
		while (tmp)
		{
			if (f_cmp((const char *)tmp->dir->d_name, (const char *)min->dir->d_name) < 0)
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
