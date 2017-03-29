/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 20:29:48 by sescolas          #+#    #+#             */
/*   Updated: 2017/01/20 11:39:56 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_islower(int n)
{
	return (n >= 'a' && n <= 'z');
}

static int	ft_isupper(int n)
{
	return (n >= 'A' && n <= 'Z');
}

int			ft_isalpha(int n)
{
	return (ft_isupper(n) || ft_islower(n));
}
