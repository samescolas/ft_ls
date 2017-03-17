/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 19:47:13 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/17 12:35:44 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_long(char *path, t_options ops)
{
	struct stat	f_stat;

	if (lstat(path, &f_stat) < 0)
		return ;
	print_file_mode(f_stat);
	print_file_permissions(f_stat);
	print_num_links(f_stat);
	print_group_info(f_stat, ops);
	print_file_size(f_stat);
}

static void	print_filename(char *path, char *filename, t_options ops)
{
	if (ops.G)
	{
		if (is_dir(path))
			write(1, "\x1B[32m", 5);
		else
			write(1, "\x1B[35m", 5);
	}
	write(1, filename, ft_strlen(filename));
	write(1, "\n", 1);
	if (ops.G)
		write(1, "\x1b[0m", 5);
}

/*
void	print_list(t_dirlist *list, t_options ops)
{
	t_dirlist	*tmp;
	char		*full_path;

	tmp = list;
	while (tmp != (void *)0)
	{
		if (!tmp)
			return ;
		full_path = ft_strjoin(&((list->path)[2]), list->dir->d_name);
		if (ops.l || ops.g)
			print_long(full_path, ops);
		else
			write(1, tmp->dir->d_name, ft_strlen(tmp->dir->d_name));
		write(1, "\n", 1);
		tmp = tmp->next;
		ft_strdel(&full_path);
	}
}
*/
void	print_list(t_dirlist *list, t_options ops)
{
	char	*full_path;

	if (!list)
		return ;
	while (list)
	{
		if ((list->path)[0] == '.')
			full_path = ft_strjoin(&((list->path)[2]), list->dir->d_name);
		else if ((list->path)[0] == '/')
			full_path = ft_strjoin(list->path, list->dir->d_name);
		else
			full_path = ft_strjoin("", list->dir->d_name);
		if (ops.l || ops.g)
			print_long(full_path, ops);
		print_filename(full_path, list->dir->d_name, ops);
		list = list->next;
		ft_strdel(&full_path);
	}
}
