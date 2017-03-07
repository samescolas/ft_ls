/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 10:24:58 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/06 20:35:07 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "../libft/libft.h"

typedef enum 
{ 
	FALSE,
	TRUE 
}	t_bool;

typedef struct			s_dirlist
{
	struct dirent		*dir;
	struct s_dirlist	*next;
}						t_dirlist;

typedef struct	s_options
{
	t_bool		R;
	t_bool		l;
	t_bool		a;
	t_bool		r;
	t_bool		t;
}				t_options;

t_options		*init_options(void);
t_options		*get_options(char *options);

#endif
