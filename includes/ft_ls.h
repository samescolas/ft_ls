/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 10:24:58 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/17 12:25:29 by sescolas         ###   ########.fr       */
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
#include <pwd.h>
#include <grp.h>
#include "../libft/libft.h"

typedef enum 
{ 
	FALSE,
	TRUE 
}	t_bool;

typedef struct			s_dirlist
{
	struct dirent		*dir;
	char				*path;
	struct s_dirlist	*next;
}						t_dirlist;

typedef struct	s_options
{
	t_bool		R;
	t_bool		l;
	t_bool		a;
	t_bool		r;
	t_bool		t;
	t_bool		g;
	t_bool		G;
}				t_options;

t_options		*init_options(void);
t_options		*get_options(char *options);
t_dirlist		*create_list_item(struct dirent *p_dir, char *path);
t_dirlist		*pop_list(t_dirlist **list);
t_dirlist		*scan_directory(char *path, t_options ops);
void			push_list(t_dirlist **list, t_dirlist *node);
void			append_list(t_dirlist **list, t_dirlist *node);
void			sort_list(t_dirlist **list, int (*f_cmp)(const char *, const char *), t_options op);
void			print_list(t_dirlist *list, t_options ops);
void			free_node(t_dirlist *node);
void			free_list(t_dirlist **list);
int				cmp_time_modified(const char *fp1, const char *fp2);
DIR				*get_dir(char *path);
int				is_dir(char *path);
void			print_file_permissions(struct stat f_stat);
void			print_file_size(struct stat f_stat);
void			print_group_info(struct stat f_stat, t_options ops);
void			print_num_links(struct stat f_stat);
void			print_file_mode(struct stat f_stat);


#endif
