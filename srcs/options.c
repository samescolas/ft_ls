/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 12:27:16 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/21 19:38:27 by sescolas         ###   ########.fr       */
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
		ret->one = FALSE;
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
		else if (*options == 'g')
			ret->g = TRUE;
		else if (*options == 'G')
			ret->G = TRUE;
		else if (*options == '1')
			ret->one = TRUE;
		else
		{
			write(2, "option not recognized\n", 22);
			exit(1);
		}
		++options;
	}
	return (ret);
}
