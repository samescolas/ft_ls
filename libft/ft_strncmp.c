/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 11:36:04 by sescolas          #+#    #+#             */
/*   Updated: 2017/01/20 10:44:33 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n-- < 1)
		return (0);
	while (*s1 && *s2 && n > 0)
	{
		if (*s1 != *s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		++s1;
		++s2;
		--n;
	}
	if (!*s1)
	{
		if (!*s2)
			return (0);
		else
			return (*(unsigned char *)s2 * -1);
	}
	if (!s2)
		return (*(unsigned char *)s1);
	else
		return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
