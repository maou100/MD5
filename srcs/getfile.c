/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 07:44:19 by feedme            #+#    #+#             */
/*   Updated: 2019/05/05 12:53:54 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

void		getfile(t_flags *flags, char *name)
{
	char			*msg;
	t_paths			*new;
	unsigned int	len;

	len = 0;
	msg = get_content(name, &len, 0);
	new = new_node();
	new->filename = ft_strdup(name);
	new->type = 'f';
	new->len = len;
	new->msg = msg;
	new->next = flags->paths;
	flags->paths = new;
}

char		*get_content(char *name, unsigned int *len, int fd)
{
	char			buf[1024];
	char			*msg;
	char			*tmp;
	int				ret;
	DIR				*dirp;

	if ((fd = open(name, O_RDONLY)) < 0)
		return (NULL);
	if ((dirp = fdopendir(fd)))
	{
		ft_printf("%s is a directory, proceeding...\n\n", ft_strdup(name));
		closedir(dirp);
	}
	ft_bzero(buf, 1024);
	msg = ft_strnew(0);
	while ((ret = read(fd, buf, 1024)) > 0)
	{
		tmp = ft_memjoin(msg, buf, *len, ret);
		free(msg);
		msg = tmp;
		*len += (unsigned int)ret;
	}
	close(fd);
	return (msg);
}
