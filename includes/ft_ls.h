/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 10:24:58 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/20 18:54:06 by sescolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include "../libft/libft.h"

# define MAX_PATH 4096

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

typedef struct	s_lengths
{
	size_t		num_links;
	size_t		pwd;
	size_t		grp;
	size_t		f_size;
	size_t		total;
}				t_lengths;

t_options		*init_options(void);
t_options		*get_options(char *options);
t_dirlist		*create_list_item(struct dirent *p_dir, char *path);
t_dirlist		*pop_list(t_dirlist **list);
t_dirlist		*scan_directory(char *path, t_options ops);
void			push_list(t_dirlist **list, t_dirlist *node);
void			append_list(t_dirlist **list, t_dirlist *node);
void			sort_list(t_dirlist **list, int (*f_cmp)(t_dirlist *, t_dirlist *), t_options op);
void			print_list(t_dirlist *list, t_options ops);
void			free_node(t_dirlist *node);
void			free_list(t_dirlist **list);
int				cmp_time_modified(t_dirlist *f1, t_dirlist *f2);
int				cmp_filename(t_dirlist *f1, t_dirlist *f2);
DIR				*get_dir(char *path);
int				is_dir(char *path);
void			print_file_permissions(struct stat f_stat);
void			print_file_size(struct stat f_stat, size_t offset);
void			print_group_info(struct stat f_stat, t_options ops, size_t o1, size_t o2);
void			print_num_links(struct stat f_stat, size_t offset);
void			print_file_mode(struct stat f_stat);
void			print_time(struct stat f_stat);
t_lengths		*get_max_lengths(t_dirlist *list);

#endif
