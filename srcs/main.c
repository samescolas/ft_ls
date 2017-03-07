/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 09:53:29 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/06 20:44:52 by sescolas         ###   ########.fr       */
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

void	print_contents(DIR *directory, t_options ops)
{
	struct dirent	*dp;
	t_dirlist		*list;

	while ((dp = readdir(directory)) != NULL)
		if (dp->d_name[0] != '.' || ops.a)
			write(1, ft_strjoin(dp->d_name, "\n"), ft_strlen(dp->d_name) + 1);
}

int		main(int argc, char **argv)
{
	DIR				*dirp;
	struct dirent	*dp;
	t_options		*ops;

	if (argc > 0 && argc < 4)
	{
		ops = (argc < 3 ? init_options() : get_options(argv[2]));
		dirp = (argc == 1 ? get_dir(".") : get_dir(argv[1]));
		print_contents(dirp, *ops);
		closedir((DIR *)dirp);
	}
	else
		write(1, "\n", 1);
	return (0);
}
