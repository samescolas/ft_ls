/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 09:09:56 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/09 12:31:37 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>
#include <time.h>

int		cmp_time_modified(const char *fp1, const char *fp2)
{
	struct stat f1_stat;
	struct stat	f2_stat;
	long		t1;
	long		t2;

	if (stat(fp1, &f1_stat) < 0 || stat(fp2, &f2_stat) < 0)
		return (0);
	t1 = f1_stat.st_mtime;
	t2 = f2_stat.st_mtime;
	if (t1 == t2)
		return (ft_strcmp(fp1, fp2));
	else
		return (t1 > t2 ? -1 : 1);
}
