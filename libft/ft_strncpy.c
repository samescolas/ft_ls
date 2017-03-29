/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 15:30:19 by sescolas          #+#    #+#             */
/*   Updated: 2017/01/17 15:57:36 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	letters_copied;
	char	*head;

	letters_copied = 0;
	head = dst;
	while (letters_copied < len)
	{
		if (*src)
			*dst++ = *src++;
		else
			*dst++ = '\0';
		++letters_copied;
	}
	return (head);
}
