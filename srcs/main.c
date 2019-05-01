/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 14:24:43 by feedme            #+#    #+#             */
/*   Updated: 2019/04/29 23:32:25 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

void	helper2(t_flags flags, t_paths *path, unsigned char *hashed)
{
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
		!ft_strcmp(flags.hash, "md5") ? ft_printf("MD5") : ft_printf("SHA256");
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
	hashed = !ft_strcmp(flags.hash, "md5") ?
	md5((unsigned char*)path->msg, path->len) : sha256((unsigned char*)path->msg, path->len);
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
	hashed = !ft_strcmp(flags.hash, "md5") ?
	md5((unsigned char*)path->msg, path->len) :
	sha256((unsigned char*)path->msg, path->len);
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
	flags = get_args(ac, av);
	if (!flags.paths || flags.p)
		get_stdin(&flags);
	flags = sort_paths(flags);
	hashish(flags);
	return (0);
}
