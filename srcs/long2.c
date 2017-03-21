/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 11:00:38 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/20 14:33:10 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	older_than_6_months(unsigned long modification_time)
{
	return (time((void *)0) - modification_time > 3600 * 24 * 180);
}

void	print_time(struct stat f_stat)
{
	char	*t;

	t = ctime((const time_t *)&(f_stat.st_mtime));
	if (older_than_6_months(f_stat.st_mtime))
	{
		write(1, &(t[4]), ft_strlen(t) - 19);
		write(1, " ", 1);
		write(1, &(t[19]), 5);
	}
	else
		write(1, &(t[4]), ft_strlen(t) - 13);
	write(1, " ", 1);
}
