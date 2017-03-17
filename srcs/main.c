/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 09:53:29 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/17 12:13:15 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_linked_list(t_dirlist *list)
{
	if (!list)
		return ;
	while (list)
	{
		if (!list->path)
			return ;
		write(1, list->dir->d_name, ft_strlen(list->dir->d_name));
		write(1, "\t", 1);
		write(1, list->path, ft_strlen(list->path));
		write(1, "\n", 1);
		list = list->next;
	}
}

void	ft_ls(char *path, t_options ops, int first)
{
	t_dirlist		*list;
	t_dirlist		*head;
	t_dirlist		*node;
	char			*full_path;

	list = (void *)0;
	if (!first)
	{
		write(1, "\n", 1);
		write(1, path, ft_strlen(path));
		write(1, ":\n", 2);
	}
	list = scan_directory(path, ops);
	head = list;
	print_list(list, ops);
	if (ops.R)
	{
		while ((node = pop_list(&list)))
		{
			full_path = ft_strjoin(node->path, node->dir->d_name);
			if (ft_strcmp(node->dir->d_name, ".") &&
					ft_strcmp(node->dir->d_name, "..") && is_dir(full_path))
				ft_ls(full_path, ops, 0);
			ft_strdel(&full_path);
			free_node(node);
		}
	}
	else
		free_list(&head);
}

int		main(int argc, char **argv)
{
	DIR				*dirp;
	DIR				*dp;
	t_options		*ops;

	if (argc == 1)
	{
		ops = init_options();
		ft_ls(".", *ops, 1);
	}
	else if ((ops = get_options(argv[1])) == (void *)0)
	{
		ops = init_options();
		ft_ls(argv[1], *ops, 1);
	}
	else
		ft_ls((argc == 2 ? "." : argv[2]), *ops, 1);
	return (0);
}
