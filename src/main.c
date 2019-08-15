/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 16:30:31 by erlazo            #+#    #+#             */
/*   Updated: 2019/07/04 19:09:04 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


// some sort of exit with freeing function...
//	zn+1 = z*z + c do this about 50 times for each point/pixel on coordinate system, 

int		ft_usage(char *str)
{
	ft_putstr(str);
	return (0);
}

int		ft_find(char *str, char **tab)				// add to lib???
{
	int		i;

	i = 0;
	while (tab[i])
	{
		if (ft_strcmp(str, tab[i]) == 0)
		{
//			printf("found\n");
			return (i);
		}
		++i;
	}
	return (-1);
}

void	ft_inp_n_fill(char *str, t_list **files)	// better if not void?
{
	static char *tab[] = {"none", "mendelbrot", "julia"};
	t_list		*new;
	int			i;

	i = ft_find(str, tab);
//	printf("found at %d\n", i);
	
	if ((/*i = ft_find(str, tab)*/ i == -1) || !(new = ft_lstcreate((void*)str, i)))
	{
		ft_lstdel(files, &ft_lstdel_cnt);
		ft_usage("usage: fractol <name>\nNames:\nmendlebrot\njulia\n");
		return ;//(NULL);
	}
//	printf("new cont size: %zu\n", new->content_size);
	ft_lstappend(files, new);
//	ft_lstprint(*files);
//	return (files);
}

int		main(int ac, char **av)
{
	int			i;
	t_list		*files;

	i = 1;
	if (ac < 2)
		return (ft_usage("usage: fractol <name>\nNames:\nmendelbrot\njulia\n"));
	else
	{
		files = NULL;
		while (i < ac)
			ft_inp_n_fill(av[i++], &files);

//		printf("main test1\n");

		ft_fractal(files);
	}
	return (0);
}

