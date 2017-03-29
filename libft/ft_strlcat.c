/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 17:32:49 by sescolas          #+#    #+#             */
/*   Updated: 2017/01/20 10:41:40 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	int		bytes_remaining;
	size_t	ret;

	ret = ft_strlen(dst);
	bytes_remaining = size - ret - 1;
	if (bytes_remaining <= 0)
		return (ret + ft_strlen(src) + bytes_remaining + 1);
	while (*dst)
		dst++;
	ret += ft_strlen(src);
	while (bytes_remaining != 0)
	{
		--bytes_remaining;
		*dst++ = *src++;
		if (!*src)
			break ;
	}
	*dst = '\0';
	return (ret);
}
