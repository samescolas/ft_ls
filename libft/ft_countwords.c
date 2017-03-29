/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countwords.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 10:28:23 by sescolas          #+#    #+#             */
/*   Updated: 2017/01/14 16:24:26 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_countwords(const char *s, char c)
{
	int words;

	if (!c)
		c = ' ';
	while (*s && *s == c)
		s++;
	words = 0;
	while (*s)
	{
		++words;
		while (*s && *s != c)
			++s;
		while (*s && *s == c)
			++s;
	}
	return (words);
}
