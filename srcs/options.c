/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 12:27:16 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/22 19:18:55 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_options	*init_options(void)
{
	t_options *ret;

	ret = (t_options *)malloc(sizeof(t_options));
	if (ret)
	{
		ret->R = FALSE;
		ret->l = FALSE;
		ret->a = FALSE;
		ret->r = FALSE;
		ret->t = FALSE;
		ret->g = FALSE;
		ret->G = FALSE;
		ret->multiple_files = FALSE;
		ret->one = FALSE;
	}
	return (ret);
}

void		add_options(char *options, t_options *ops)
{

	if (!*options || *options++ != '-')
		return ;
	while (*options)
	{
		if (*options == 'R')
			ops->R = TRUE;
		else if (*options == 'l')
			ops->l = TRUE;
		else if (*options == 'a')
			ops->a = TRUE;
		else if (*options == 'r')
			ops->r = TRUE;
		else if (*options == 't')
			ops->t = TRUE;
		else if (*options == 'g')
			ops->g = TRUE;
		else if (*options == 'G')
			ops->G = TRUE;
		else if (*options == '1')
			ops->one = TRUE;
		else
		{
			write(1, "ft_ls: illegal option -- ", 25);
			write(1, options, 1);
			write(1, "\nusage: ft_ls [-RGaglrt1] [file ...]\n", 37);
			exit(1);
		}
		++options;
	}
}
