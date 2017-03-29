/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 20:00:08 by sescolas          #+#    #+#             */
/*   Updated: 2017/01/20 10:31:30 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const char	*source;
	char		*destination;

	source = src;
	destination = dst;
	while (n > 0)
	{
		ft_memset(destination++, *source++, 1);
		n--;
	}
	return (dst);
}
