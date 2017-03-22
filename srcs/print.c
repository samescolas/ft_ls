/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 19:47:13 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/21 19:10:06 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_long(char *path, t_options ops, t_lengths *maxes)
{
	struct stat	f_stat;

	if (lstat(path, &f_stat) < 0)
		return ;
	print_file_mode(f_stat);
	print_file_permissions(f_stat);
	print_num_links(f_stat, maxes->num_links);
	print_group_info(f_stat, ops, maxes->pwd, maxes->grp);
	print_file_size(f_stat, maxes->f_size);
	print_time(f_stat);
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
	if (ops.G)
		write(1, "\x1b[0m", 5);
}

void	print_linked_to_file(char *filepath)
{
	struct stat	f_stat;
	char		buf[MAX_PATH];

	if (lstat(filepath, &f_stat) < 0)
		return ;
	if (!S_ISLNK(f_stat.st_mode))
	{
		write(1, "\n", 1);
		return ;
	}
	write(1, " -> ", 4);
	ft_bzero(buf, MAX_PATH);
	if (readlink(filepath, (char *)&buf, 100) > 0)
		write(1, buf, ft_strlen(buf));
	write(1, "\n", 1);
}

void	print_list(t_dirlist *list, t_options ops)
{
	char		*full_path;
	t_lengths	*maxes;

	if (!list)
		return ;
	if (ops.l || ops.g)
	{
		maxes = get_max_lengths(list);
		write(1, "total ", 6);
		ft_putnbr(maxes->total);
		write(1, "\n", 1);
	}
	while (list)
	{
		if ((list->path)[0] == '.')
			full_path = ft_strjoin(&((list->path)[2]), list->dir->d_name);
		else if ((list->path)[0] == '/')
			full_path = ft_strjoin(list->path, list->dir->d_name);
		else
			full_path = ft_strjoin("", list->dir->d_name);
		if (ops.l || ops.g)
			print_long(full_path, ops, maxes);
		print_filename(full_path, list->dir->d_name, ops);
		if (ops.l || ops.g)
			print_linked_to_file(full_path);
		else
			write(1, "\n", 1);
		list = list->next;
		ft_strdel(&full_path);
	}
}
