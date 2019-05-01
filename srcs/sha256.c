/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 18:15:00 by feedme            #+#    #+#             */
/*   Updated: 2019/04/30 23:46:59 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

unsigned int	*init_shavars(t_sha *vars, unsigned char *inp, unsigned int len)
{
	unsigned char		*tmp;

	tmp = (unsigned char*)malloc(8);
	vars->h0 = 0x6a09e667;
	vars->h1 = 0xbb67ae85;
	vars->h2 = 0x3c6ef372;
	vars->h3 = 0xa54ff53a;
	vars->h4 = 0x510e527f;
	vars->h5 = 0x9b05688c;
	vars->h6 = 0x1f83d9ab;
	vars->h7 = 0x5be0cd19;
	vars->msg = prepare_inp(inp, len);
	vars->new_len = find_len(len);
	tmp = ft_memrev(tmp, vars->msg + vars->new_len - 8, 8);
	ft_memcpy(vars->msg + vars->new_len - 8, tmp, 8);
	free(tmp);
	return (create_k());
}

void			build_tmp2(t_sha *vars, t_tmp *t, unsigned char *inp)
{
	unsigned int		i;
	unsigned int		j;

	i = -1;
	j = 0;
	while (++i < 16)
	{
		ft_memrev(t->tab2 + i, inp + j, 4);
		j += 4;
	}
	while (i < 64)
	{
		t->tab2[i] = (r_rot(t->tab2[i - 2], 17) ^ r_rot(t->tab2[i - 2], 19) ^
(t->tab2[i - 2] >> 10)) + t->tab2[i - 7] + (r_rot(t->tab2[i - 15], 7) ^
r_rot(t->tab2[i - 15], 18) ^ (t->tab2[i - 15] >> 3)) + t->tab2[i - 16];
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

void			update_vars(t_tmp *tmp)
{
	unsigned int		i;

	i = -1;
	while (++i < 64)
	{
		tmp->s1 = r_rot(tmp->e, 6) ^ r_rot(tmp->e, 11) ^ r_rot(tmp->e, 25);
		tmp->ch = (tmp->e & tmp->f) ^ (~tmp->e & tmp->g);
		tmp->tmp1 = tmp->h + tmp->s1 + tmp->ch + tmp->k[i] + tmp->tab2[i];
		tmp->s0 = r_rot(tmp->a, 2) ^ r_rot(tmp->a, 13) ^ r_rot(tmp->a, 22);
		tmp->maj = (tmp->a & tmp->b) ^ (tmp->a & tmp->c) ^ (tmp->b & tmp->c);
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

unsigned char	*sha_digest(t_sha vars)
{
	unsigned char	*new;
	unsigned int				i;

	i = -1;
	new = (unsigned char*)malloc(65);
	while (++i < 65)
		new[i] = 0;
	insert_intsha(new, vars.h0);
	insert_intsha(new + 8, vars.h1);
	insert_intsha(new + 16, vars.h2);
	insert_intsha(new + 24, vars.h3);
	insert_intsha(new + 32, vars.h4);
	insert_intsha(new + 40, vars.h5);
	insert_intsha(new + 48, vars.h6);
	insert_intsha(new + 56, vars.h7);
	return (new);
}

unsigned char	*sha256(unsigned char *inp, unsigned int len)
{
	t_sha			vars;
	unsigned int				i;
	t_tmp			tmp;

	i = 0;
	tmp.k = init_shavars(&vars, inp, len);
	while (i < vars.new_len)
	{
		build_tmp2(&vars, &tmp, vars.msg + i);
		update_vars(&tmp);
		vars.h0 = vars.h0 + tmp.a;
		vars.h1 = vars.h1 + tmp.b;
		vars.h2 = vars.h2 + tmp.c;
		vars.h3 = vars.h3 + tmp.d;
		vars.h4 = vars.h4 + tmp.e;
		vars.h5 = vars.h5 + tmp.f;
		vars.h6 = vars.h6 + tmp.g;
		vars.h7 = vars.h7 + tmp.h;
		i += 64;
	}
	free(vars.msg);
	return (sha_digest(vars));
}
