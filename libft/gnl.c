/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 11:00:08 by erlazo            #+#    #+#             */
/*   Updated: 2019/05/28 18:21:07 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		gnl(char **l, char **s, int b_size, int fd)
{
	ssize_t	i;
	char	*p;
	char	b[b_size + 1];

	p = NULL;
	if ((i = ft_findchar(*s, DELIM)) != -1)
	{
		if (!(*l = ft_strsub(*s, 0, (size_t)i++))
			|| (!(p = ft_strsub(*s, i, ft_strlen(*s) - (size_t)i))))
			return (-1);
		free(*s);
		*s = p;
		return (1);
	}
	ft_bzero(b, b_size + 1);
	if ((i = read(fd, b, b_size)) < 0
		|| (i > 0 && !(p = ft_strjoin(*s, b)))
		|| (*s[0] && ++i == 1 && !(p = ft_strjoin(*s, "\n"))))
		return (-1);
	free(*s);
	*s = p;
	return ((i > 0) ? gnl(l, s, b_size, fd) : 0);
}
