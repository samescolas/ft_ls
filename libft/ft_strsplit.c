/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 15:52:21 by sescolas          #+#    #+#             */
/*   Updated: 2017/01/20 12:07:25 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_strsplit(const char *s, char c)
{
	char	**arr;
	int		i;

	if (!s)
		return (NULL);
	arr = (char **)malloc((ft_countwords(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	while (*s && *s == c)
		++s;
	while (*s)
	{
		arr[i++] = ft_strsub(s, 0, ft_strfind((char *)s, c));
		while (*s && *s != c)
			++s;
		while (*s && *s == c)
			++s;
	}
	arr[i] = (void *)0;
	return (arr);
}
