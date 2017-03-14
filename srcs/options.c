/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 12:27:16 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/13 14:06:33 by sescolas         ###   ########.fr       */
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
	}
	return (ret);
}

t_options	*get_options(char *options)
{
	t_options	*ret;

	if (!*options || *options++ != '-')
		return ((void *)0);
	ret = init_options();
	while (*options)
	{
		if (*options == 'R')
			ret->R = TRUE;
		else if (*options == 'l')
			ret->l = TRUE;
		else if (*options == 'a')
			ret->a = TRUE;
		else if (*options == 'r')
			ret->r = TRUE;
		else if (*options == 't')
			ret->t = TRUE;
		else
		{
			write(2, "option not recognized\n", 22);
			exit(1);
		}
		++options;
	}
	return (ret);
}
