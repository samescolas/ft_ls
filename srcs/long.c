/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 12:58:18 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/23 16:57:33 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_file_mode(struct stat f_stat, t_bool opG)
{
	if (opG)
		write(1, BLU, 5);
	if (S_ISLNK(f_stat.st_mode))
		pad_str("l", 0, (opG ? MAG : (void *)0));
	else if (S_ISBLK(f_stat.st_mode))
		pad_str("b", 0, (opG ? BLU : (void *)0));
	else if (S_ISCHR(f_stat.st_mode))
		pad_str("c", 0, (opG ? BLU : (void *)0));
	else if (S_ISDIR(f_stat.st_mode))
		pad_str("d", 0, (opG ? BLU : (void *)0));
	else if (S_ISSOCK(f_stat.st_mode))
		pad_str("s", 0, (opG ? BL2 : (void *)0));
	else if (S_ISFIFO(f_stat.st_mode))
		pad_str("p", 0, (opG ? BL2 : (void *)0));
	else
		pad_str("-", 0, (opG ? BK2 : (void *)0));
}

void	print_num_links(struct stat f_stat, size_t offset, t_bool opG)
{
	pad_num(f_stat.st_nlink, 
			-1 * (offset - ft_numlen(f_stat.st_nlink)),
			(opG ? CY3 : (void *)0));
	write(1, " ", 1);
}

void	print_group_info(struct stat f_stat, t_options ops, t_lengths maxes, t_bool opG)
{
	struct group	*grp;
	struct passwd	*pwd;

	pwd = getpwuid(f_stat.st_uid);
	grp = getgrgid(f_stat.st_gid);
	if (!ops.g)
	{
		if (pwd == NULL)
			pad_num(f_stat.st_uid, ft_numlen(maxes.pwd - f_stat.st_uid),
				(opG ? BL2 : (void *)0));
		else if (f_stat.st_uid == 0)
			pad_str("root", maxes.pwd - 4, (opG ? BL2 : (void *)0));
		else
			pad_str(pwd->pw_name, maxes.pwd - ft_strlen(pwd->pw_name),
					(opG ? BL2 : (void *)0));
		write(1, "  ", 2);
	}
	if (grp == NULL)
		pad_num(f_stat.st_uid, maxes.grp - ft_numlen(f_stat.st_uid),
				(opG ? BLU : (void *)0));
	else
		pad_str(grp->gr_name, maxes.grp - ft_strlen(grp->gr_name) + 2,
				(opG ? BLU : (void *)0));
}

void	print_file_size(struct stat f_stat, t_lengths maxes, t_bool opG)
{
	size_t	offset;

	if (S_ISCHR(f_stat.st_mode) || S_ISBLK(f_stat.st_mode))
	{
		pad_num(major(f_stat.st_rdev),
				-1 * (maxes.major - ft_numlen(major(f_stat.st_rdev)) + 1),
				(opG ? MG2 : (void *)0));
		pad_str(",", 1, (opG ? MG2 : (void *)0));
		pad_num(minor(f_stat.st_rdev),
				-1 * (maxes.minor - ft_numlen(minor(f_stat.st_rdev))),
				(opG ? MG2 : (void *)0));
		write(1, " ", 1);
	}
	else
	{
		if (maxes.f_size > maxes.minor + maxes.major + 3)
			offset = maxes.f_size;
		else
			offset = maxes.minor + maxes.major + 3;
		pad_num(f_stat.st_size, -1 * (offset - ft_numlen(f_stat.st_size)),
				opG ? CY1 : (void *)0);
		write(1, " ", 1);
	}
}

void	print_file_permissions(struct stat f_stat, t_bool opG)
{
	if (opG)
		write(1, CY1, 5);
	write(1, (f_stat.st_mode & S_IRUSR) ? "r" : "-", 1);
	write(1, (f_stat.st_mode & S_IWUSR) ? "w" : "-", 1);
	if (f_stat.st_mode & S_ISUID)
		write(1, (f_stat.st_mode & S_IXUSR) ? "s" : "S", 1);
	else
		write(1, (f_stat.st_mode & S_IXUSR) ? "x" : "-", 1);
	if (opG)
		write(1, BL2, 5);
	write(1, (f_stat.st_mode & S_IRGRP) ? "r" : "-", 1);
	write(1, (f_stat.st_mode & S_IWGRP) ? "w" : "-", 1);
	if (f_stat.st_mode & S_ISGID)
		write(1, (f_stat.st_mode & S_IXGRP) ? "s" : "S", 1);
	else
		write(1, (f_stat.st_mode & S_IXGRP) ? "x" : "-", 1);
	if (opG)
		write(1, CY2, 5);
	write(1, (f_stat.st_mode & S_IROTH) ? "r" : "-", 1);
	write(1, (f_stat.st_mode & S_IWOTH) ? "w" : "-", 1);
	if (f_stat.st_mode & S_ISVTX)
		write(1, (f_stat.st_mode & S_IXOTH) ? "t" : "T", 1);
	else
		write(1, (f_stat.st_mode & S_IXOTH) ? "x" : "-", 1);
	write(1, "  ", 2);
}
