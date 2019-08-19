/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyhook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamart <erlazo@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 17:58:28 by erlazo            #+#    #+#             */
/*   Updated: 2019/08/19 18:59:40 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		ft_redraw(t_fract *mlx, int i)
{
	char *str;

	mlx_destroy_image(mlx->ptr, mlx->tab[i].img_ptr);
	if (!(mlx->tab[i].img_ptr = mlx_new_image(mlx->ptr, mlx->tab[i].win_width,
		mlx->tab[i].win_height)))
		return (0);
	mlx->tab[i].img_data = (int*)mlx_get_data_addr(mlx->tab[i].img_ptr,
	&mlx->bpp, &mlx->s_l, &mlx->endian);
	ft_draw(mlx, i);
	mlx_clear_window(mlx->ptr, mlx->tab[i].win_ptr);
	mlx_put_image_to_window(mlx->ptr, mlx->tab[i].win_ptr, mlx->tab[i].img_ptr, 0, 0);
	if (mlx->tab[i].disp_info == 1)
	{
		str = ft_strjoin("Precition:", ft_itoa(mlx->tab[i].max_iter));
		str = ft_strjoin(str, " Zoom:");
		str = ft_strjoin(str, ft_itoa(mlx->tab[i].zoom));
		str = ft_strjoin(str, " X:");
		str = ft_strjoin(str, ft_itoa(mlx->tab[i].x_o));
		str = ft_strjoin(str, " Y:");
		str = ft_strjoin(str, ft_itoa(mlx->tab[i].y_o));
		mlx_string_put(mlx->ptr, mlx->tab[i].win_ptr, 0, 0, 0xFFFFFF, str);


/*
		str = ft_strjoin(ft_strjoin(ft_strjoin("precition:",\
		ft_itoa(mlx->tab[i].max_iter)), ft_strjoin(" zoom:",\
		ft_itoa(mlx->tab[i].zoom))), ft_strjoin(ft_strjoin(" x:",\
		ft_itoa(mlx->tab[i].x_o)), ft_strjoin(" y:",\
		ft_itoa(mlx->tab[i].y_o))));
		mlx_string_put(mlx->ptr, mlx->tab[i].win_ptr, 0, 0, 0xFFFFFF, str);
*/	}
	return (0);
}

void	ft_init_more(t_key *torch)		// don't need most of these keys....
{
/*	torch[11].keycode = 17;
	torch[11].f = &ft_rot_z_left;
	torch[12].keycode = 16
	torch[12].f = &ft_rot_z_right;
	torch[13].keycode = 32;
	torch[13].f = &ft_rot_x_left;
	torch[14].keycode = 5;
	torch[14].f = &ft_rot_x_right;
	torch[15].keycode = 4;
	torch[15].f = &ft_rot_y_left;
	torch[16].keycode = 38;
	torch[16].f = &ft_rot_y_right;
	torch[17].keycode = 126;
	torch[17].f = &ft_raise_sealevel;
	torch[18].keycode = 125;
	torch[18].f = &ft_lower_sealevel;
*/
/*
	torch[19].keycode = 27;				// don't really need this ???
	torch[19].f = ft_zoom_out;
	torch[20].keycode = 24;
	torch[20].f = ft_zoom_in;
*/
/*	torch[21].keycode = 35;
	torch[21].f = ft_proj_type;			*/
}

void	ft_init_keytorch(t_key *torch)
{
	torch[0].keycode = 53;
	torch[0].f = &ft_quitfract;
	
	torch[1].keycode = 15;
	torch[1].f = ft_resetfract;
	torch[2].keycode = 34;
	torch[2].f = ft_display_info;
	torch[3].keycode = 24;
	torch[3].f = ft_more_precise;
	torch[4].keycode = 27;
	torch[4].f = ft_less_precise;
	

/*
	torch[3].keycode = ;
	torch[3].f = ;
*/
	torch[5].keycode = 124;
	torch[5].f = ft_pan_right;
	torch[6].keycode = 123;
	torch[6].f = ft_pan_left;
	torch[7].keycode = 126;
	torch[7].f = ft_pan_up;
	torch[8].keycode = 125;
	torch[8].f = ft_pan_down;

/*	torch[1].keycode = 116;
	torch[1].f = &ft_increase_altitude;
	torch[2].keycode = 121;
	torch[2].f = &ft_decrease_altitude;
	torch[3].keycode = 13;
	torch[3].f = &ft_up;
	torch[4].keycode = 1;
	torch[4].f = &ft_down;
	torch[5].keycode = 0;
	torch[5].f = &ft_left;
	torch[6].keycode = 2;
	torch[6].f = &ft_right;
	torch[7].keycode = 69;
	torch[7].f = ft_zoom_in;
	torch[8].keycode = 78;
	torch[8].f = ft_zoom_out;
	torch[9].keycode = 8;
	torch[9].f = ft_color;
	torch[10].keycode = 49;
	torch[10].f = &ft_change_projection;		*/
	ft_init_more(torch);
}

int		ft_keyhook(int keycode, void *param)		// o this better ? not re inited?
{
	t_ol			*tab;
	static t_key	keytab[42] = {{42, NULL}};
	int				i;

	i = 0;
	tab = (t_ol*)param;
	if (keytab[0].keycode == 42)
		ft_init_keytorch(keytab);
	while (i < 22)					// should have 2 dif sets so can call f with mlx...
	{
		if (keycode == keytab[i].keycode)
			return (keytab[i].f(tab));
		i++;
	}
	return (0);
}

void	ft_hooks_loop(t_fract *mlx, int i)
{
	mlx_hook(mlx->tab[i].win_ptr, 2, 0, &ft_keyhook, &mlx->tab[i]);
	mlx_hook(mlx->tab[i].win_ptr, 4, 0, &ft_mouse_press, &mlx->tab[i]);
	mlx_hook(mlx->tab[i].win_ptr, 5, 0, &ft_mouse_release, &mlx->tab[i]);
	mlx_hook(mlx->tab[i].win_ptr, 6, 0, &ft_mouse_move, &mlx->tab[i]);
	mlx_hook(mlx->tab[i].win_ptr, 17, 0, &ft_quitone, &mlx->tab[i]);		// seems to quit
}																	// everything...





