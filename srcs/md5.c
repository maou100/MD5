/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 18:05:59 by feedme            #+#    #+#             */
/*   Updated: 2019/05/03 15:47:23 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

void			helper(t_tmp *t, t_md5 v, unsigned int g, unsigned int *f)
{
	*f = *f + t->a + v.k[t->i] + t->tab[g];
	t->a = t->d;
	t->d = t->c;
	t->c = t->b;
}

void			update_tmp(t_tmp *tmp, t_md5 v, unsigned int g, unsigned int f)
{
	while (tmp->i < 64)
	{
		if (tmp->i < 16)
		{
			f = ((tmp->b & tmp->c) | (~(tmp->b) & tmp->d));
			g = tmp->i;
		}
		else if (tmp->i < 32)
		{
			f = ((tmp->d & tmp->b) | (~(tmp->d) & tmp->c));
			g = ((tmp->i * 5) + 1) % 16;
		}
		else if (tmp->i < 48)
		{
			f = (tmp->b ^ tmp->c ^ tmp->d);
			g = ((3 * tmp->i) + 5) % 16;
		}
		else if (tmp->i < 64)
		{
			f = tmp->c ^ (tmp->b | ~(tmp->d));
			g = (7 * tmp->i) % 16;
		}
		helper(tmp, v, g, &f);
		tmp->b = tmp->b + left_rot(f, v.s[tmp->i++]);
	}
}

void			get_chunk(unsigned int *tab, unsigned char *msg)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (i < 16)
	{
		ft_memcpy(tab + i, msg + j, 4);
		j += 4;
		i++;
	}
}

unsigned char	*build_digest(t_md5 vars)
{
	unsigned char	*new;
	unsigned int	i;

	i = -1;
	new = (unsigned char*)malloc(33);
	while (++i < 33)
		new[i] = 0;
	insert_int(new, vars.a0);
	insert_int(new + 8, vars.b0);
	insert_int(new + 16, vars.c0);
	insert_int(new + 24, vars.d0);
	return (new);
}

unsigned char	*md5(unsigned char *inp, unsigned int len)
{
	t_md5			vars;
	unsigned int	i;
	t_tmp			tmp;

	i = 0;
	init_var(&vars, inp, len);
	while (i < vars.new_len)
	{
		tmp.i = 0;
		tmp.a = vars.a0;
		tmp.b = vars.b0;
		tmp.c = vars.c0;
		tmp.d = vars.d0;
		get_chunk(tmp.tab, &vars.msg[i]);
		update_tmp(&tmp, vars, 0, 0);
		vars.a0 += tmp.a;
		vars.b0 += tmp.b;
		vars.c0 += tmp.c;
		vars.d0 += tmp.d;
		i += 64;
	}
	free(vars.msg);
	return (build_digest(vars));
}
