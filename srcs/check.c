/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 08:28:59 by feedme            #+#    #+#             */
/*   Updated: 2019/05/03 15:39:35 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

int		check_opts(char **av, int *i, int j)
{
	if (av[*i][j] != 'p' && av[*i][j] != 'q' &&
	av[*i][j] != 'r' && av[*i][j] != 's')
	{
		ft_printf("ft_ssl: %s: bad option -- %c", ft_strdup(av[1]), av[*i][j]);
		ft_printf("\nuse: %s [-pqr] [-s str] [files ..]\n", ft_strdup(av[1]));
		exit(0);
	}
	if (av[*i][j] == 's')
	{
		if (!av[*i][j + 1] && !av[*i + 1])
		{
			ft_printf("%s: option needs arg -- s\nusage: ", ft_strdup(av[1]));
			ft_printf("%s [-pqr] [-s str] [files ...]\n", ft_strdup(av[1]));
			exit(0);
		}
		if (!av[*i][j + 1])
		{
			(*i)++;
			return (0);
		}
		else
			return (0);
	}
	return (1);
}

void	check_args(int ac, char **av)
{
	int		i;
	int		j;

	i = 1;
	if (ft_strcmp(av[1], "md5") && ft_strcmp(av[1], "sha256") &&
ft_strcmp(av[1], "sha512"))
	{
		ft_printf("ft_ssl: Error: '%s' is an invalid comman", ft_strdup(av[1]));
		ft_printf("d.\n\nStandard commands:\n\nMessage Digest Commands:\nmd5");
		ft_printf("\nsha256\nsha512\n\nCipher commands:\n");
		exit(0);
	}
	while (++i < ac)
	{
		j = 0;
		if (av[i][0] == '-')
		{
			while (av[i][++j])
			{
				if (!check_opts(av, &i, j))
					break ;
			}
		}
	}
}
