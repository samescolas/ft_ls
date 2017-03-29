/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprime.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 14:52:55 by sescolas          #+#    #+#             */
/*   Updated: 2017/01/14 16:27:15 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_primehelper(int n, int guess)
{
	if (n < 2)
		return (0);
	if (guess < 2)
		return (1);
	if (n % guess == 0)
		return (0);
	return (ft_primehelper(n, guess - 1));
}

int				ft_isprime(int n)
{
	return (ft_primehelper(n, ft_sqrt(n)));
}
