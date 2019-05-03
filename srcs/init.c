/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 17:09:32 by feedme            #+#    #+#             */
/*   Updated: 2019/05/03 15:40:15 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

int						**init_tmp(void)
{
	int				**tmp;
	int				i;

	i = -1;
	tmp = (int**)malloc(sizeof(int*) * 4);
	while (++i < 4)
		tmp[i] = (int*)malloc(sizeof(int) * 4);
	tmp[0][0] = 7;
	tmp[0][1] = 12;
	tmp[0][2] = 17;
	tmp[0][3] = 22;
	tmp[1][0] = 5;
	tmp[1][1] = 9;
	tmp[1][2] = 14;
	tmp[1][3] = 20;
	tmp[2][0] = 4;
	tmp[2][1] = 11;
	tmp[2][2] = 16;
	tmp[2][3] = 23;
	tmp[3][0] = 6;
	tmp[3][1] = 10;
	tmp[3][2] = 15;
	tmp[3][3] = 21;
	return (tmp);
}

unsigned int			get_value(int i)
{
	double			res;

	res = sin(i + 1);
	if (res < 0)
		res *= -1;
	return ((unsigned int)(res * 4294967296));
}

int						find_len(int len)
{
	int				new;

	new = 64;
	while ((new - 8) <= len)
		new += 64;
	return (new);
}

unsigned char			*prepare_inp(unsigned char *inp, int len)
{
	unsigned char	*new;
	int				new_len;
	uint64_t		tmp2;

	new_len = find_len(len);
	new = (unsigned char*)malloc(new_len);
	ft_bzero(new, new_len);
	new = ft_memcpy(new, inp, len);
	new[len] = 128;
	tmp2 = (len * 8);
	ft_memcpy(&new[new_len - 8], &tmp2, 8);
	return (new);
}

void					init_var(t_md5 *vars, unsigned char *inp,
unsigned int len)
{
	int				**tmp;
	int				i;
	int				j;

	i = -1;
	j = -1;
	tmp = init_tmp();
	while (++i < 64)
	{
		vars->k[i] = 0;
		if (!(i % 16))
			j++;
		vars->s[i] = tmp[j][i % 4];
	}
	i = -1;
	while (++i < 4)
		free(tmp[i]);
	free(tmp);
	if (prep_vars(vars))
		i = -1;
	while (++i < 64)
		vars->k[i] = get_value(i);
	vars->msg = prepare_inp(inp, len);
	vars->new_len = find_len(len);
}
