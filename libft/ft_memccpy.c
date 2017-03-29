/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 20:00:08 by sescolas          #+#    #+#             */
/*   Updated: 2017/01/20 10:30:29 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t bytes_copied;

	bytes_copied = 0;
	while (bytes_copied < n)
	{
		*(unsigned char *)dst = *(unsigned char *)src;
		dst += 1;
		if (*(unsigned char *)src == (unsigned char)c)
			return (dst);
		src += 1;
		++bytes_copied;
	}
	return (NULL);
}
