/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 12:58:18 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/16 10:35:05 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_file_mode(struct stat f_stat)
{
	if (S_ISLNK(f_stat.st_mode))
		write(1, "l", 1);
	else if (S_ISBLK(f_stat.st_mode))
		write(1, "b", 1);
	else if (S_ISCHR(f_stat.st_mode))
		write(1, "c", 1);
	else if (S_ISDIR(f_stat.st_mode))
		write(1, "d", 1);
	else if (S_ISSOCK(f_stat.st_mode))
		write(1, "s", 1);
	else if (S_ISFIFO(f_stat.st_mode))
		write(1, "p", 1);
	else
		write(1, "_", 1);
}

void	print_num_links(struct stat f_stat)
{
	nlink_t	num_links;

	num_links = f_stat.st_nlink;
	ft_putnbr((int)num_links);
	write(1, " ", 1);
}

void	print_group_info(struct stat f_stat, t_options ops)
{
	struct group	*grp;
	struct passwd	*pwd;

	pwd = getpwuid(f_stat.st_uid);
	grp = getgrgid(f_stat.st_gid);

	if (!ops.g)
	{
		if (pwd == 0)
			write(1, "root ", 5);
		else
			write(1, pwd->pw_name, ft_strlen(pwd->pw_name));
		write(1, "  ", 2);
	}
	if (grp == 0)
		write(1, "root ", 5);
	else
		write(1, grp->gr_name, ft_strlen(grp->gr_name));
	write(1, "  ", 2);
}

void	print_file_size(struct stat f_stat)
{
	int	i;

	i = 0;
	while (i++ + ft_numlen(f_stat.st_size) < 6)
		write(1, " ", 1);
	ft_putnbr(f_stat.st_size);
	write(1, " ", 1);
}

void	print_file_permissions(struct stat f_stat)
{
	write(1, (f_stat.st_mode & S_IRUSR) ? "r" : "_", 1);
	write(1, (f_stat.st_mode & S_IWUSR) ? "w" : "_", 1);
	write(1, (f_stat.st_mode & S_IXUSR) ? "x" : "_", 1);
	write(1, (f_stat.st_mode & S_IRGRP) ? "r" : "_", 1);
	write(1, (f_stat.st_mode & S_IWGRP) ? "w" : "_", 1);
	write(1, (f_stat.st_mode & S_IXGRP) ? "x" : "_", 1);
	write(1, (f_stat.st_mode & S_IROTH) ? "r" : "_", 1);
	write(1, (f_stat.st_mode & S_IWOTH) ? "w" : "_", 1);
	write(1, (f_stat.st_mode & S_IXOTH) ? "x  " : "_  ", 3);
}
