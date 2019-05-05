/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 14:24:43 by feedme            #+#    #+#             */
/*   Updated: 2019/05/05 12:55:54 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

void	helper2(t_flags flags, t_paths *path, unsigned char *hashed)
{
	int		i;

	i = -1;
	if (flags.r)
	{
		ft_printf("%s ", ft_strdup((char*)hashed));
		if (path->type == 'f')
			ft_printf("%s\n", ft_strdup(path->filename));
		else
			ft_printf("\"%s\"\n", path->msg);
	}
	else
	{
		while (flags.hash[++i])
			ft_printf("%c", ft_toupper(flags.hash[i]));
		if (path->type == 'f')
			ft_printf(" (%s) = ", ft_strdup(path->filename));
		else
			ft_printf(" (\"%s\") = ", path->msg);
		ft_printf("%s\n", ft_strdup((char*)hashed));
	}
}

void	hashishian(t_flags flags, t_paths *path)
{
	unsigned char	*hashed;

	hashed = NULL;
	hashed = (*g_fcts[flags.code])((unsigned char*)path->msg, path->len);
	if (flags.q)
		ft_printf("%s\n", ft_strdup((char*)hashed));
	else
		helper2(flags, path, hashed);
	if (hashed)
		free(hashed);
}

void	inp_outp(t_flags flags, t_paths *path)
{
	unsigned char	*hashed;

	hashed = NULL;
	hashed = (*g_fcts[flags.code])((unsigned char*)path->msg, path->len);
	if (flags.p)
		ft_printf("%s", ft_strdup(path->msg));
	ft_printf("%s\n", ft_strdup((char*)hashed));
	if (hashed)
		free(hashed);
}

void	hashish(t_flags flags)
{
	t_paths	*head;

	head = flags.paths;
	while (flags.paths)
	{
		if (!flags.paths->msg)
			ft_printf("ft_ssl: %s: %s: No such file or directory\n",
			ft_strdup(flags.hash), ft_strdup(flags.paths->filename));
		else
		{
			if (flags.paths->type == 'i')
				inp_outp(flags, flags.paths);
			else
				hashishian(flags, flags.paths);
		}
		flags.paths = flags.paths->next;
	}
	flags.paths = head;
}

int		main(int ac, char **av)
{
	t_flags	flags;

	if (ac == 1)
		ft_exit_msg("usage: ft_ssl command [command opts] [command args]\n");
	g_fcts[0] = &md5;
	g_fcts[1] = &sha256;
	g_fcts[2] = &sha512;
	flags = get_args(ac, av);
	if (!flags.paths || flags.p)
		get_stdin(&flags);
	flags = sort_paths(flags);
	hashish(flags);
	return (0);
}
