/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 07:38:45 by feedme            #+#    #+#             */
/*   Updated: 2019/04/29 18:23:32 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

unsigned int	r_rot(unsigned int f, unsigned int s)
{
	return ((f >> s) | (f << (32 - s)));
}

unsigned int	left_rot(unsigned int f, unsigned int s)
{
	return ((f << s) | (f >> (32 - s)));
}

t_flags			sort_paths(t_flags flags)
{
	t_paths	*stdin;
	t_paths	*rev;
	t_paths	*tmp;

	rev = NULL;
	stdin = NULL;
	if (flags.paths && flags.paths->type == 'i')
	{
		stdin = flags.paths;
		flags.paths = flags.paths->next;
	}
	while (flags.paths)
	{
		tmp = flags.paths->next;
		flags.paths->next = rev;
		rev = flags.paths;
		flags.paths = tmp;
	}
	flags.paths = rev;
	if (stdin)
	{
		stdin->next = flags.paths;
		flags.paths = stdin;
	}
	return (flags);
}

void			init_flags(t_flags *flags)
{
	flags->hash = NULL;
	flags->p = 0;
	flags->q = 0;
	flags->r = 0;
	flags->s = 0;
	flags->paths = NULL;
}

t_paths			*new_node(void)
{
	t_paths	*new;

	if (!(new = (t_paths*)malloc(sizeof(t_paths))))
		return (NULL);
	new->filename = NULL;
	new->type = 0;
	new->len = 0;
	new->msg = NULL;
	new->next = NULL;
	return (new);
}
