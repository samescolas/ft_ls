/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 10:24:58 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/07 20:00:52 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include <dirent.h>
#include <sys/stat.h>
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
t_dirlist		*create_list_item(struct dirent *p_dir);
t_dirlist		*pop_list(t_dirlist **list);
t_dirlist		*scan_directory(DIR *dir, t_options ops);
void			push_list(t_dirlist **list, t_dirlist *node);
void			append_list(t_dirlist **list, t_dirlist *node);
void			sort_list(t_dirlist **list, int (*f_cmp)(const char *, const char *));
void			print_list(t_dirlist *list, t_options ops);
void			print_file_permissions(char *filename);

#endif
