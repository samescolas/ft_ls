/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 18:32:03 by sescolas          #+#    #+#             */
/*   Updated: 2017/01/14 16:49:02 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	chars_copied;
	char	*head;

	head = s1;
	chars_copied = 0;
	while (*s1)
		s1++;
	while (chars_copied < n && *s2)
	{
		*s1++ = *s2++;
		chars_copied++;
	}
	*s1 = '\0';
	return (head);
}
