/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 18:16:51 by sescolas          #+#    #+#             */
/*   Updated: 2017/01/14 16:50:18 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = ft_strlen((char *)s);
	while (*s)
		s++;
	if (!c)
		return ((char *)s);
	--s;
	while (len)
	{
		if ((char)*s == c)
			return ((char *)s);
		s--;
		--len;
	}
	return (NULL);
}
