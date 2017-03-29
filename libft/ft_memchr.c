/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 10:39:22 by sescolas          #+#    #+#             */
/*   Updated: 2017/01/20 10:30:49 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t bytes_copied;

	bytes_copied = 0;
	while (bytes_copied < n)
	{
		if (*(unsigned char *)s == (unsigned char)c)
			return ((void *)s);
		s += 1;
		++bytes_copied;
	}
	return (NULL);
}
