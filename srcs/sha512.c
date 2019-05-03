/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 01:11:51 by feedme            #+#    #+#             */
/*   Updated: 2019/05/03 15:44:04 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

void			build_512(t_sha512 *vars, t_tmp512 *t, unsigned char *inp)
{
	unsigned int		i;
	unsigned int		j;

	i = -1;
	j = 0;
	while (++i < 16)
	{
		ft_memrev(t->w + i, inp + j, 8);
		j += 8;
	}
	while (i < 80)
	{
		t->w[i] = (r_rot64(t->w[i - 15], 1) ^ r_rot64(t->w[i - 15], 8) ^
(t->w[i - 15] >> 7)) + t->w[i - 7] + (r_rot64(t->w[i - 2], 19) ^
r_rot64(t->w[i - 2], 61) ^ (t->w[i - 2] >> 6)) + t->w[i - 16];
		i++;
	}
	t->a = vars->h0;
	t->b = vars->h1;
	t->c = vars->h2;
	t->d = vars->h3;
	t->e = vars->h4;
	t->f = vars->h5;
	t->g = vars->h6;
	t->h = vars->h7;
}

void			update_512(t_tmp512 *tmp)
{
	unsigned int		i;

	i = -1;
	while (++i < 80)
	{
		tmp->s1 = r_rot64(tmp->e, 14) ^ r_rot64(tmp->e, 18) ^
r_rot64(tmp->e, 41);
		tmp->ch = tmp->g ^ (tmp->e & (tmp->f ^ tmp->g));
		tmp->tmp1 = tmp->h + tmp->s1 + tmp->ch + tmp->k[i] + tmp->w[i];
		tmp->s0 = r_rot64(tmp->a, 28) ^ r_rot64(tmp->a, 34) ^
r_rot64(tmp->a, 39);
		tmp->maj = ((tmp->a & tmp->b) | (tmp->c & (tmp->a | tmp->b)));
		tmp->tmp2 = tmp->s0 + tmp->maj;
		tmp->h = tmp->g;
		tmp->g = tmp->f;
		tmp->f = tmp->e;
		tmp->e = tmp->d + tmp->tmp1;
		tmp->d = tmp->c;
		tmp->c = tmp->b;
		tmp->b = tmp->a;
		tmp->a = tmp->tmp1 + tmp->tmp2;
	}
}

void			insert_intsha512(unsigned char *str, unsigned long val)
{
	int				i;
	char			*base;

	i = 16;
	base = base_tmp();
	while (--i > -1)
	{
		str[i] = base[val % 16];
		val /= 16;
	}
	free(base);
}

unsigned char	*sha512_digest(t_sha512 vars)
{
	unsigned char	*new;
	unsigned int	i;

	i = -1;
	new = (unsigned char*)malloc(129);
	while (++i < 129)
		new[i] = 0;
	insert_intsha512(new, vars.h0);
	insert_intsha512(new + 16, vars.h1);
	insert_intsha512(new + 32, vars.h2);
	insert_intsha512(new + 48, vars.h3);
	insert_intsha512(new + 64, vars.h4);
	insert_intsha512(new + 80, vars.h5);
	insert_intsha512(new + 96, vars.h6);
	insert_intsha512(new + 112, vars.h7);
	return (new);
}

unsigned char	*sha512(unsigned char *inp, unsigned int len)
{
	t_sha512			vars;
	unsigned int		i;
	t_tmp512			tmp;

	i = 0;
	tmp.k = init_sha512(&vars, inp, len);
	while (i < vars.new_len)
	{
		build_512(&vars, &tmp, vars.msg + i);
		update_512(&tmp);
		vars.h0 = vars.h0 + tmp.a;
		vars.h1 = vars.h1 + tmp.b;
		vars.h2 = vars.h2 + tmp.c;
		vars.h3 = vars.h3 + tmp.d;
		vars.h4 = vars.h4 + tmp.e;
		vars.h5 = vars.h5 + tmp.f;
		vars.h6 = vars.h6 + tmp.g;
		vars.h7 = vars.h7 + tmp.h;
		i += 128;
	}
	free(vars.msg);
	return (sha512_digest(vars));
}
