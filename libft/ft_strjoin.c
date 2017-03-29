/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 12:33:19 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/17 12:30:08 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char *new_str;
	char *ret_str;

	if (!s1 || !s2)
		return (NULL);
	new_str = ft_strnew((ft_strlen((char *)s1) + ft_strlen((char *)s2)));
	if (!new_str)
		return (NULL);
	ret_str = new_str;
	while (*s1)
		*new_str++ = *s1++;
	while (*s2)
		*new_str++ = *s2++;
	*new_str = '\0';
	return (ret_str);
}
