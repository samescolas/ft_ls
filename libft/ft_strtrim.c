/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 12:38:45 by sescolas          #+#    #+#             */
/*   Updated: 2017/01/20 11:41:42 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_iswhitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\r' ||
			c == '\n' || c == '\f' || c == '\v');
}

static int	ft_ctleadwhitespace(char *s)
{
	int		ct;

	ct = 0;
	while (s[ct] && ft_iswhitespace(s[ct]))
		++ct;
	return (ct);
}

static int	ft_cttrailwhitespace(char *s)
{
	int		ct;

	ct = 0;
	while (*(s + 1))
		++s;
	while (*s)
	{
		if (!ft_iswhitespace(*s--))
			break ;
		++ct;
	}
	return (ct);
}

char		*ft_strtrim(const char *s)
{
	char	*str;
	char	*head;
	int		len;

	if (!s)
		return (NULL);
	len = ft_strlen((char *)s) - ft_ctleadwhitespace((char *)s)
		- ft_cttrailwhitespace((char *)s);
	if (len < 0)
		return (ft_strnew(0));
	head = (char *)malloc((len + 1) * sizeof(char));
	if (head)
	{
		str = head;
		while (*s && ft_iswhitespace(*s))
			++s;
		while (len)
		{
			*str++ = *s++;
			--len;
		}
		*str = '\0';
	}
	return (head);
}
