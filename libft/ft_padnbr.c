/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_padnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 11:55:58 by sescolas          #+#    #+#             */
/*   Updated: 2017/01/20 12:05:42 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_padnbr(int n, int offset, char *color)
{
	while (offset++ < 0)
		write(1, " ", 1);
	--offset;
	if (color)
		write(1, color, ft_strlen(color));
	ft_putnbr(n);
	while (offset-- > 0)
		write(1, " ", 1);
	if (color)
		write(1, DEFAULT, 4);
}
