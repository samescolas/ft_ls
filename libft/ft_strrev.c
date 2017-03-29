/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 11:15:48 by sescolas          #+#    #+#             */
/*   Updated: 2017/01/17 15:59:22 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *s)
{
	char	*rev;
	char	*head;
	int		len;

	len = ft_strlen(s);
	head = ft_strnew(len);
	if (head)
	{
		rev = head;
		while (*s)
			++s;
		while (len)
		{
			--len;
			*rev++ = (*--s);
		}
	}
	return (head);
}
