/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 18:47:09 by feedme            #+#    #+#             */
/*   Updated: 2019/04/30 23:49:02 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# include "libftprintf.h"
# include <math.h>

typedef struct		s_paths
{
	char			*filename;
	char			type;
	char			*msg;
	unsigned int	len;
	struct s_paths	*next;
}					t_paths;

typedef struct		s_tmp
{
	unsigned int	a;
	unsigned int	b;
	unsigned int	c;
	unsigned int	d;
	unsigned int	e;
	unsigned int	f;
	unsigned int	g;
	unsigned int	h;
	unsigned int	tab[16];
	unsigned int	tab2[64];
	unsigned int	i;
	unsigned int	s0;
	unsigned int	s1;
	unsigned int	ch;
	unsigned int	maj;
	unsigned int	tmp1;
	unsigned int	tmp2;
	unsigned int	*k;
}					t_tmp;

typedef struct		s_tmp512
{
	unsigned long	a;
	unsigned long	b;
	unsigned long	c;
	unsigned long	d;
	unsigned long	e;
	unsigned long	f;
	unsigned long	g;
	unsigned long	w[80];
	unsigned long	s0;
	unsigned long	s1;
	unsigned long	ch;
	unsigned long	maj;
	unsigned long	tmp1;
	unsigned long	tmp2;
	unsigned long	*k;
unsigned long	h;

}					t_tmp512;

typedef struct		s_sha512
{
	unsigned long	h0;
	unsigned long	h1;
	unsigned long	h2;
	unsigned long	h3;
	unsigned long	h4;
	unsigned long	h5;
	unsigned long	h6;
	unsigned long	h7;
	unsigned int	og_len;

}					t_sha512;


typedef struct		s_sha
{

	unsigned int	h0;
	unsigned int	h1;
	unsigned int	h2;
	unsigned int	h3;
	unsigned int	h4;
	unsigned int	h5;
	unsigned int	h6;
	unsigned int	h7;
	unsigned int	s0;
	unsigned int	s1;
	unsigned char	*msg;
	unsigned int	og_len;
	unsigned int	new_len;
}					t_sha;

typedef struct		s_md5
{
	unsigned int	s[64];
	unsigned int	k[64];
	unsigned int	a0;
	unsigned int	b0;
	unsigned int	c0;
	unsigned int	d0;
	unsigned char	*msg;
	unsigned int	new_len;
}					t_md5;

typedef struct		s_flags
{
	char			p;
	char			q;
	char			r;
	char			s;
	char			*hash;
	t_paths			*paths;
}					t_flags;

unsigned int		*create_k(void);
void				insert_intsha(unsigned char *str, unsigned int val);
int					find_len(int len);
unsigned char		*prepare_inp(unsigned char *inp, int len);
int					prep_vars(t_md5 *vars);
unsigned char		*sha256(unsigned char *inp, unsigned int len);
unsigned char		*md5(unsigned char *inp, unsigned int len);
t_paths				*new_node(void);
void				init_flags(t_flags *flags);
void				free_all(t_flags *flags);
void				getfile(t_flags *flags, char *name);
char				*get_content(char *name, unsigned int *len);
void				get_stdin(t_flags *flags);
void				check_args(int ac, char **av);
t_flags				get_args(int ac, char **av);
void				check_args(int ac, char **av);
int					check_opts(char **av, int *i, int j);
void				init_vars(t_md5 *vars, unsigned char *inp, unsigned int len);
t_flags				sort_paths(t_flags flags);
unsigned int		left_rot(unsigned int f, unsigned int s);
void				insert_int(unsigned char *str, unsigned int val);
char				*base_tmp(void);
unsigned int		r_rot(unsigned int f, unsigned int s);

#endif
