/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 19:47:13 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/14 17:25:54 by sescolas         ###   ########.fr       */
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

static void	print_filename(char *filename, t_options ops)
{
	if (ops.G)
	{
		if (is_dir(filename))
			write(1, "\x1B[32m", 5);
		else
			write(1, "\x1B[35m", 5);
	}
	write(1, filename, ft_strlen(filename));
	write(1, "\n", 1);
	if (ops.G)
		write(1, "\x1b[0m", 5);
}

void	print_list(t_dirlist *list, char *path, t_options ops)
{
	char	*full_path;

	while (list)
	{
		full_path = ft_strjoin(list->path, list->dir->d_name);
		if (ops.l || ops.g)
			print_long(full_path, ops);
		print_filename(full_path, ops);
		list = list->next;
	}
}


