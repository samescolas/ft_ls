/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 12:27:16 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/24 18:16:50 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_error_message(char option, t_ops *ops)
{
	write(2, "ft_ls: illegal option -- ", 25);
	write(2, &option, 1);
	write(2, "\nusage: ft_ls [-GRafglrt1] [file ...]\n", 38);
	ft_bzero(ops, sizeof(t_ops));
	free(ops);
	exit(1);
}

t_ops		*init_ops(void)
{
	t_ops *ret;

	ret = (t_ops *)malloc(sizeof(t_ops));
	if (ret)
	{
		ret->recurse = FALSE;
		ret->l = FALSE;
		ret->a = FALSE;
		ret->r = FALSE;
		ret->t = FALSE;
		ret->g = FALSE;
		ret->f = FALSE;
		ret->color = FALSE;
		ret->multiple_files = FALSE;
		ret->one = FALSE;
	}
	return (ret);
}

static void	add_option(char op, t_ops *ops)
{
	if (op == 'R')
		ops->recurse = TRUE;
	else if (op == 'l')
		ops->l = TRUE;
	else if (op == 'a')
		ops->a = TRUE;
	else if (op == 'r')
		ops->r = TRUE;
	else if (op == 't')
		ops->t = TRUE;
	else if (op == 'g')
		ops->g = TRUE;
	else if (op == 'G')
		ops->color = TRUE;
	else if (op == 'f')
	{
		ops->f = TRUE;
		ops->a = TRUE;
	}
	else if (op == '1')
		ops->one = TRUE;
	else
		print_error_message(op, ops);
}

void		add_options(char *options, t_ops *ops)
{
	static t_bool	end_of_options;

	if (end_of_options)
	{
		load_error_message(create_arg_node(options), *ops);
		return ;
	}
	if (!*options || *options++ != '-')
		return ;
	while (*options)
	{
		if (ft_strcmp(options - 1, "--") == 0)
		{
			end_of_options = TRUE;
			return ;
		}
		else if (*options == '-')
			print_error_message(*options, ops);
		add_option(*options++, ops);
	}
}
