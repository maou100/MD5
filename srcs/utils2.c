/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 18:14:15 by feedme            #+#    #+#             */
/*   Updated: 2019/04/30 23:23:55 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

int				prep_vars(t_md5 *vars)
{
	vars->a0 = 0x67452301;
	vars->b0 = 0xefcdab89;
	vars->c0 = 0x98badcfe;
	vars->d0 = 0x10325476;
	return (1);
}

char			*base_tmp(void)
{
	char			*new;

	new = malloc(16);
	new[0] = '0';
	new[1] = '1';
	new[2] = '2';
	new[3] = '3';
	new[4] = '4';
	new[5] = '5';
	new[6] = '6';
	new[7] = '7';
	new[8] = '8';
	new[9] = '9';
	new[10] = 'a';
	new[11] = 'b';
	new[12] = 'c';
	new[13] = 'd';
	new[14] = 'e';
	new[15] = 'f';
	return (new);
}

void			free_all(t_flags *flags)
{
	t_paths	*tmp;

	if (flags->hash)
		free(flags->hash);
	while (flags->paths)
	{
		if (flags->paths->filename)
			free(flags->paths->filename);
		tmp = flags->paths->next;
		if (flags->paths->msg)
			free(flags->paths->msg);
		free(flags->paths);
		flags->paths = tmp;
	}
	exit(0);
}

void			insert_int(unsigned char *str, unsigned int val)
{
	int				i;
	unsigned int	*new_val;
	char			*base;

	i = 8;
	base = base_tmp();
	new_val = malloc(sizeof(unsigned int));
	new_val = ft_memrev(new_val, &val, 4);
	while (--i > -1)
	{
		str[i] = base[*new_val % 16];
		*new_val /= 16;
	}
	free(base);
	free(new_val);
}

void			insert_intsha(unsigned char *str, unsigned int val)
{
	int				i;
	char			*base;

	i = 8;
	base = base_tmp();
	while (--i > -1)
	{
		str[i] = base[val % 16];
		val /= 16;
	}
	free(base);
}
