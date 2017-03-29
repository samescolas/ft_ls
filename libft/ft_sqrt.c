/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 14:59:26 by sescolas          #+#    #+#             */
/*   Updated: 2017/01/20 10:35:05 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_sqrthelper(long long n, long long guess)
{
	if (guess <= 0)
		return (0);
	if ((guess * guess) <= n)
		return (guess);
	return (ft_sqrthelper(n, guess - 1));
}

int			ft_sqrt(int n)
{
	return (ft_sqrthelper(n, n));
}
