/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scandir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 08:40:29 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/07 12:20:17 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dirlist	*scan_directory(DIR *dir, t_options ops)
{
	struct dirent	*dp;
	t_dirlist		*list;

	if ((dp = readdir(dir)) != NULL)
		list = create_list_item(dp);
	while ((dp = readdir(dir)) != NULL)
		if (dp->d_name[0] != '.' || ops.a)
			push_list(&list, create_list_item(dp));
	return (list);
}
