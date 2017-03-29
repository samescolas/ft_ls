/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 17:05:02 by sescolas          #+#    #+#             */
/*   Updated: 2017/01/20 10:32:26 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	void	*tmp;

	tmp = malloc(len);
	if (tmp)
	{
		ft_memcpy(tmp, src, len);
		ft_memcpy(dst, tmp, len);
	}
	free(tmp);
	return (dst);
}
