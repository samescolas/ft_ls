/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 19:47:13 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/07 20:00:38 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_list(t_dirlist *list, t_options ops)
{
	while (list)
	{
		if (ops.l)
			print_file_permissions(list->dir->d_name);
		write(1, " ", 1);
		write(1, list->dir->d_name, ft_strlen(list->dir->d_name));
		write(1, "\n", 1);
		list = list->next;
	}
}

void	print_file_permissions(char *filename)
{
	struct stat f_stat;

	if (stat(filename, &f_stat) < 0)
		return;
	write(1, (S_ISDIR(f_stat.st_mode)) ? "d" : "_", 1);
	write(1, (f_stat.st_mode & S_IRUSR) ? "r" : "_", 1);
	write(1, (f_stat.st_mode & S_IWUSR) ? "w" : "_", 1);
	write(1, (f_stat.st_mode & S_IXUSR) ? "x" : "_", 1);
	write(1, (f_stat.st_mode & S_IRGRP) ? "r" : "_", 1);
	write(1, (f_stat.st_mode & S_IWGRP) ? "w" : "_", 1);
	write(1, (f_stat.st_mode & S_IXGRP) ? "x" : "_", 1);
	write(1, (f_stat.st_mode & S_IROTH) ? "r" : "_", 1);
	write(1, (f_stat.st_mode & S_IWOTH) ? "w" : "_", 1);
	write(1, (f_stat.st_mode & S_IXOTH) ? "x" : "_", 1);
}
