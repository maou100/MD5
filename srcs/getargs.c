/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getargs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 07:46:17 by feedme            #+#    #+#             */
/*   Updated: 2019/05/03 15:38:29 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

void		get_stdin(t_flags *flags)
{
	t_paths			*new;
	char			buf[1024];
	char			*msg;
	char			*tmp;
	int				ret;

	ft_bzero(buf, 1024);
	msg = ft_strnew(0);
	new = new_node();
	while ((ret = read(0, buf, 1024)) > 0)
	{
		new->len += ret;
		tmp = ft_strjoin(msg, buf);
		free(msg);
		msg = tmp;
	}
	new->type = 'i';
	new->msg = msg;
	new->next = flags->paths;
	flags->paths = new;
}

void		get_opts(char **av, int *i, t_flags *flags)
{
	int		j;
	t_paths	*tmp;

	j = 0;
	while (av[*i][++j])
	{
		if (av[*i][j] == 'p')
			flags->p = 1;
		if (av[*i][j] == 'q')
			flags->q = 1;
		if (av[*i][j] == 'r')
			flags->r = 1;
		if (av[*i][j] == 's')
		{
			tmp = new_node();
			tmp->type = 's';
			tmp->msg = av[*i][j + 1] ?
			ft_strdup(av[*i] + j + 1) : ft_strdup(av[++(*i)]);
			tmp->len = ft_strlen(tmp->msg);
			flags->s = 1;
			tmp->next = flags->paths;
			flags->paths = tmp;
			return ;
		}
	}
}

t_flags		get_args(int ac, char **av)
{
	int		i;
	t_flags	flags;

	i = 1;
	check_args(ac, av);
	init_flags(&flags);
	flags.hash = ft_strdup(av[1]);
	if (!ft_strcmp(flags.hash, "md5"))
		flags.code = 0;
	else if (!ft_strcmp(flags.hash, "sha256"))
		flags.code = 1;
	else if (!ft_strcmp(flags.hash, "sha512"))
		flags.code = 2;
	while (++i < ac && av[i][0] == '-')
		get_opts(av, &i, &flags);
	while (i < ac)
	{
		getfile(&flags, av[i]);
		i++;
	}
	return (flags);
}
