/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 10:54:56 by sescolas          #+#    #+#             */
/*   Updated: 2017/01/20 10:39:50 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strfind(char *str, char c)
{
	int	len;

	len = 0;
	while (str[len])
	{
		if (str[len] == c)
			return (len);
		++len;
	}
	return (len);
}
