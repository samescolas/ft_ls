/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sescolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 10:24:58 by sescolas          #+#    #+#             */
/*   Updated: 2017/03/23 18:03:50 by sescolas         ###   ########.fr       */
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

# define DEF "\x1B[0m"
# define RED "\x1B[31m"
# define GRN "\x1B[32m"
# define YLW "\x1B[33m"
# define BLU "\x1B[34m"
# define MAG "\x1B[35m"
# define CY1 "\x1B[36m"
# define CY2 "\x1B[37m"
# define BK2 "\x1B[90m"
# define RD2 "\x1B[91m"
# define GR2 "\x1B[92m"
# define YL2 "\x1B[93m"
# define BL2 "\x1B[94m"
# define MG2 "\x1B[95m"
# define CY3 "\x1B[96m"

typedef enum 
{ 
	FALSE,
	TRUE 
}	t_bool;

typedef struct		s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	struct dirent	*dir;
	char			*path;
}					t_btree;

typedef struct	s_options
{
	t_bool		R;
	t_bool		l;
	t_bool		a;
	t_bool		r;
	t_bool		t;
	t_bool		g;
	t_bool		G;
	t_bool		one;
	t_bool		multiple_files;
}				t_options;

typedef struct	s_lengths
{
	size_t		num_links;
	size_t		pwd;
	size_t		grp;
	size_t		f_size;
	size_t		minor;
	size_t		major;
	size_t		total;
}				t_lengths;

char			*get_d_name(char *path);
t_options		*init_options(void);
void			add_options(char *options, t_options *ops);
t_btree			*scan_directory(char *path, t_options ops);
int				is_dir(char *path);
void			pad_str(char *str, int offset, char *color);
void			pad_num(int num, int offset, char *color);
void			print_file_permissions(struct stat f_stat, t_bool opG);
void			print_file_size(struct stat f_stat, t_lengths maxes, t_bool opG);
void			print_group_info(struct stat f_stat, t_options ops, t_lengths maxes, t_bool opG);
void			print_num_links(struct stat f_stat, size_t offset, t_bool opG);
void			print_file_mode(struct stat f_stat, t_bool opG);
void			print_time(struct stat f_stat, t_bool opG);
void			print_long(char *path, t_options ops, t_lengths maxes);
t_lengths		*get_max_lengths(t_btree *list, t_options ops);
void			print_tree(t_btree *tree, t_options ops);
t_btree			*create_node(struct dirent	*p_dir, char *path);
t_btree			*create_listnode(char *path);
void			btree_insert(t_btree **root, t_btree *node, t_options ops, int (*cmp)(t_btree *, t_btree *));
void			btree_apply_infix(t_btree *root, t_options ops, t_lengths *maxes, void (*applyf)(t_btree *, t_options, t_lengths *));

int				cmp_time(t_btree *f1, t_btree *f2);
int				cmp_filename(t_btree *f1, t_btree *f2);
int				cmp_args_f(t_btree *f1, t_btree *f2);
int				cmp_args_t(t_btree *f1, t_btree *f2);
void			ft_ls(char *path, t_options ops, t_bool one_and_only);



#endif
