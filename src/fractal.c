/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 17:33:54 by erlazo            #+#    #+#             */
/*   Updated: 2020/10/03 02:29:59 by ericlazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_clear_mlx(t_fract *mlx)		// now clears all remaining  windows
{
	int		i;

	i = 0;
//	printf("q all 1\n");
	while (i < mlx->n_frols)		// does tab need to be freed????
	{
		if (mlx->tab[i].type != -1)		// good that worked, although why not worth
		{								// looking into
			if (mlx->tab[i].img_ptr)
				mlx_destroy_image(mlx->ptr, mlx->tab[i].img_ptr);
			if (mlx->tab[i].win_ptr)
			{
				mlx_clear_window(mlx->ptr, mlx->tab[i].win_ptr);
				mlx_destroy_window(mlx->ptr, mlx->tab[i].win_ptr);
			}
//			printf("q all inner\n");
		}
		++i;
	}
//	printf("q all 2\n");
}

int		ft_quitone(t_ol *tab)
{
	int		i;

	i = 0;
	if (tab->img_ptr)
		mlx_destroy_image(tab->mlx->ptr, tab->img_ptr);
	if (tab->win_ptr)
	{
		mlx_clear_window(tab->mlx->ptr, tab->win_ptr);
		mlx_destroy_window(tab->mlx->ptr, tab->win_ptr);
	}

//	printf("q1\n");
	tab->type = -1;
	while (i < tab->mlx->n_frols)			// works but clear tab???
	{
		if (tab->mlx->tab[i].type != -1)// is there lib func to remove single elem???
			return (0);
		++i;
	}
//	printf("q2\n");
	return (ft_quitfract(tab));
}

int		ft_quitfract(t_ol *tab)
{
	ft_clear_mlx(tab->mlx);
	exit(0);
//	return (0);			// this is dumb as shit....
}


void	ft_abort(t_fract *mlx, t_list **list, char *err_msg)
{
	ft_clear_mlx(mlx);
//	ft_lstdel(list, ft_lstdel_cnt);
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
	while (i < mlx->n_frols)	//somehow working now
	{
//		printf("content_size: %zu\n", files->content_size);
		tab[i].type = (int)files->content_size;
		tab[i].name = (char*)files->content;
		++i;
		files = files->next;
//		printf("loop end\n");
	}
//	printf("fract test2\n");
	if (!(ft_initfractal(mlx, tab)))
		return (ft_abort(mlx, &files, "mlx_init() failed\n"));	//fix the abort??? clear table ???

	ft_lstdel(&files, &ft_lstdel_cnt);

	//need to free files...

//	printf("fract test3\n");
//	printf("n_frols: %d\n", mlx->n_frols);

	i = 0;
	while (i < mlx->n_frols)	// this is where sebfault... i need to init all wins 1st
	{
		ft_draw(mlx, i);
//		printf("fract test4\n");
		mlx_put_image_to_window(mlx->ptr, mlx->tab[i].win_ptr,\
		mlx->tab[i].img_ptr, 0, 0);

		ft_hooks_loop(mlx, i);
//		printf("fract test5\n");
		++i;
	}
	mlx_loop(mlx->ptr);
}



