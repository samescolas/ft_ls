/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 09:53:29 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/24 19:38:42 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		cleanup(t_btree *tree, t_lengths *maxes)
{
	uproot(&tree);
	ft_bzero(maxes, sizeof(t_lengths));
	free(maxes);
	maxes = (void *)0;
}

int				main(int argc, char **argv)
{
	t_btree		*args;
	t_ops		*ops;
	t_lengths	*maxes;
	int			i;

	args = (void *)0;
	ops = init_ops();
	maxes = (void *)0;
	i = 0;
	while (++i < argc && argv[i][0] == '-')
		add_options(argv[i], ops);
	if (i < argc)
		args = parse_args(&(argv[i]), argc - i, *ops);
	else
		print_contents(".", *ops, TRUE);
	ops->multiple_files = (argc - i > 1);
	if (args)
	{
		maxes = get_max_lengths(args, *ops);
		btree_apply_infix(args, *ops, maxes, &display_file);
		cleanup(args, maxes);
		/*
		uproot(&args);
		ft_bzero(maxes, sizeof(*maxes));
		free(maxes);
		*/
	}
	ft_bzero(ops, sizeof(t_ops));
	free(ops);
	return (0);
}
