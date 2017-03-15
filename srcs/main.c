/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 09:53:29 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/14 17:17:48 by sescolas         ###   ########.fr       */
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
	DIR				*dirp;
	struct dirent	*dp;
	t_dirlist		*list;
	t_dirlist		*node;

	list = (void *)0;
	write(1, "calling ls with path ", 21);
	write(1, path, ft_strlen(path));
	write(1, "\n", 1);
	if (!first)
	{
		write(1, "\n", 1);
		write(1, path, ft_strlen(path));
		write(1, ":\n", 2);
	}
	dirp = get_dir(path);
	list = scan_directory(dirp, path, ops);
	print_list(list, ft_strjoin(path, "/"), ops);
	if (ops.R)
	{
		while (list != NULL)
		{
			node = pop_list(&list);
			if (ft_strcmp(node->dir->d_name, ".") && ft_strcmp(node->dir->d_name, "..") && is_dir(ft_strjoin(path, ft_strjoin("/", node->dir->d_name))))
			{
				ft_ls(ft_strjoin(path, ft_strjoin("/", node->dir->d_name)), ops, 0);
				push_list(&list, scan_directory(get_dir(ft_strjoin(path, ft_strjoin("/", (node->dir->d_name)))), path, ops));
			}
		}
	}
	write(1, "closing dir ", 12);
	write(1, path, ft_strlen(path));
	write(1, "\n", 1);
	closedir((DIR *)dirp);
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
