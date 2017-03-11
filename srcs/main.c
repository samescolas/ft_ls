/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 09:53:29 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/09 09:23:16 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

DIR		*get_dir(char *path)
{
	DIR	*ret;

	if (path[0] == '/')
		ret = opendir(path);
	else
		ret = opendir(ft_strjoin("./", path));
	if (ret == NULL)
	{
		write(2, "invalid filename or path\n", 25);
		exit(1);
	}
	return (ret);
}

int		main(int argc, char **argv)
{
	DIR				*dirp;
	struct dirent	*dp;
	t_options		*ops;
	t_dirlist		*list;

	if (argc > 0 && argc < 4)
	{
		ops = (argc < 3 ? init_options() : get_options(argv[2]));
		dirp = (argc == 1 ? get_dir(".") : get_dir(argv[1]));
		list = scan_directory(dirp, *ops);
		sort_list(&list, &cmp_time_modified, *ops);
		print_list(list, *ops);
		closedir((DIR *)dirp);
	}
	else
		write(1, "\n", 1);
	return (0);
}
