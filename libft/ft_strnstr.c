/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 12:39:33 by sescolas          #+#    #+#             */
/*   Updated: 2017/01/13 11:37:40 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int	len_little;
	int	chars_compared;

	if (!*little)
		return ((char *)big);
	len_little = ft_strlen((char *)little);
	chars_compared = 0;
	while (*big && chars_compared < (int)len)
	{
		if (!(ft_strncmp(big, little, len_little)) &&
			(chars_compared + len_little) <= (int)len)
			return ((char *)big);
		++chars_compared;
		big++;
	}
	return (NULL);
}
