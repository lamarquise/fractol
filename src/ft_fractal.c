/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fractal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 17:33:54 by erlazo            #+#    #+#             */
/*   Updated: 2019/07/04 19:09:16 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_clear_mlx(t_fract *mlx)
{
/*	if (mlx->tabimg_ptr)
		mlx_destroy_image(mlx->ptr, mlx->img_ptr);
	if (mlx->win_ptr)
	{
		while (mlx->win_ptr->contents)
		{
			mlx_clear_window(mlx->ptr, mlx->win_ptr);
			mlx_destroy_window(mlx->ptr, mlx->win_ptr);
			mlx->win_ptr = mlx->win_ptr->next;
		}
	} */
}

int		ft_quitfract(t_fract *mlx)
{
	ft_clear_mlx(mlx);			// something else??? list clear win_ptr???
	exit(0);
	return (0);			// this is dumb as shit....
}


void	ft_abort(t_fract *mlx, t_list **list, char *err_msg)
{
	ft_clear_mlx(mlx);
	ft_lstdel(list, ft_lstdel_cnt);
	ft_putstr_fd(err_msg, 2);
}


void	ft_fractal(t_list *files)
{
	t_fract	*mlx;
	t_ol	*tab;
	int		i;
					// can i init keyhooks here ????	
	i = 0;
	mlx->n_frols = ft_lstlen(files);

//	printf("fract test1\n");
//	printf("n_frols: %d\n", mlx->n_frols);

	if (!(tab = (t_ol*)ft_memalloc(sizeof(t_ol) * mlx->n_frols)))
		return ;		//or ft_usage or not void...
//	while (i < mlx->n_frols)
//	{
		printf("content_size: %zu\n", files->content_size);
		tab[i].type = (int)files->content_size;
		tab[i].name = (char*)files->content;
//		++i;
//		files = files->next;
		printf("loop end\n");
//	}
//	printf("fract test2\n");
	if (!(ft_initfractal(mlx, tab, files)))
		return (ft_abort(mlx, &files, "mlx_init() failed\n"));	//fix the abort???

//	printf("fract test3\n");
//	printf("n_frols: %d\n", mlx->n_frols);

	i = 0;
//	while (i < mlx->n_frols)	//use a copy??? so still have start???
//	{
		ft_draw(mlx, i);
		printf("fract test4\n");
		mlx_put_image_to_window(mlx->ptr, mlx->tab[i].win_ptr, mlx->tab[i].img_ptr, 0, 0);// how to handle dif img_ptr??? dif struct for linked list, comb with win_ptr?
//		ft_hooks_loop(mlx, i);
		printf("fract test5\n");
//		++i;
//	}
//	ft_hooks_loop(mlx, i);
	mlx_loop(mlx->ptr);
}



