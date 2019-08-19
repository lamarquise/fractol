


#include "fractol.h"

int		lin_interpol(int c1, int c2, double perc)	// standard perc, always left...
{
	int		red;
	int		green;
	int		blue;		// no idea if this will work.....

//	printf("c1 red: %d\n", c1 % 256);
//	printf("c1: %d\n", c1);
/*
	red = (1 - perc) * ((c1 >> 16) & 0xFF) + perc * ((c2 >> 16) & 0xFF);
	green = (1 - perc) * ((c1 >> 8) & 0xFF) + perc * ((c2 >> 8) & 0xFF);
	return (red<<16 | green<<8 | blue);
*/

	red = (1 - perc) * c1 / 65536 + perc * c2 / 65536;
//	printf("perc: %f, c1: %d, c2: %d, red: %d\n", perc, c1 / 65536, c2 / 65536, red);	


	green = (1 - perc) * ((c1 / 256) % 256) + perc * ((c2 / 256) % 256);
	blue = (1 - perc) * (c1 % 256) + perc * (c2 % 256);


	// could put all the math in the ret, but more confusing so...

	return (red * 65536 + green * 256 + blue);
}

int		bilin_interpol(t_mag *og, int pix_start, double perc_x, double perc_y)
{
	int		color;

	if ((pix_start + 1) % og->x == 1)	// case B or D
	{
		if ((pix_start + og->x * 2) / og->x > og->y)	// case D

			return (og->img_data[pix_start]);
		else			// case B
			return (lin_interpol(og->img_data[pix_start], og->img_data[pix_start + og->x], perc_y));
	}
	else if ((pix_start + og->x * 2) / og->x > og->y)	// case C
		return (lin_interpol(og->img_data[pix_start], og->img_data[pix_start + 1], perc_x));

	// case A
	return (lin_interpol(lin_interpol(og->img_data[pix_start], og->img_data[pix_start + 1], perc_x),\
			lin_interpol(og->img_data[pix_start + og->x], og->img_data[pix_start + og->x + 1], perc_x), perc_y));
}

void	ft_resize(t_ol * tab, int old_tx, int old_ty)
{
	int		tl;
	int		i;
//	t_mag	tmp;
	void	*tmp_img_ptr;
	int		*tmp_img_data;
	int		f_x;
	int		f_y;
	double	x;
	double	y;


			// good idea to do this here but only works if it's zoom out...
/*	tab->scale /= tab->z_fact;

	tab->wid_scale /= tab->z_fact;
	tab->hei_scale /= tab->z_fact;

	tab->st_x = tab->x_o - tab->wid_scale / 2;
	tab->st_y = tab->y_o + tab->hei_scale / 2;
*/


	
















//	tmp.x = tab->win_width * 1.5;
//	tmp.y = tab->win_height * 1.5;
//	tmp.last_p = tmp.x * tmp.y;

//	printf("wid: %d, hei: %d", tmp.x, tmp.y);
//	printf(" lastp: %d\n", tmp.last_p);



	if (!(tmp_img_ptr = mlx_new_image(mlx->ptr, tab->win_width, tab->win_height)))
		return ;
//	if (!(
	tmp_img_data = (int*)mlx_get_data_addr(tmp_img_ptr,\
		tab->mlx->bpp, tab->mlx->s_l, tab->mlx->endian); //))
//		return ;
	
	i = 0;
	while (i < tab->last_pix)
	{

		// better, send old img, pos in img, ratios x and y, return color, top left pixel

		// x in new_img = i % tmp.x;
		// y in new_img = i / tmp.x;

//		printf("x in new img: %d\n", i % tmp.x);


//		x = i % tmp.x;
//		y = i / tmp.x;

		// mlx->img->x / tmp.x * x = new x in old 
		// mlx->img->y / tmp.y * y = new y in old


		x = (1 / 1.5) * (double)(i % tmp.x); // new x pos in old img
		y = (1 / 1.5) * ((double)i / tmp.x);

//		printf("new x in old img: %f\n", x);



		// floor(new x in old - 0.5) + floor(new y in old - 0.5) * mlx->img->x;	== top left pix in old
		// top left = (floor(x - 0.5) + floor(y - 0.5) * mlx->img->x);

//		printf("x: %f, y: %f\n", x, y);

		f_x = floor(x - 0.5);
		f_y = floor(y - 0.5);

		if (f_x < 0)
			f_x = 0;
		if (f_y < 0)
			f_y = 0;

		tl = f_x + f_y * mlx->img->x;

//		if (tl < 0)
//			tl = 0;

//		printf("floorx: %d, floory: %d, old img x: %d\n", (int)floor(x - 0.5), (int)floor(y - 0.5), mlx->img->x);

//		printf("top left pix: %d\n", tl);

		// percentage x = floor(new x in old - 0.5)	// wait is it ???
		// percentage y = floor(new y in old - 0.5)
		// perc_x = (x - 0.5) - floor(x - 0.5);
		// perc_y = (y - 0.5) - floor(y - 0.5);
		
//		perc_x = floor(mlx->img->x / tmp.x * (i % tmp.x) - 0.5);		
//		perc_y = floor(mlx->img->y / tmp.y * (i / tmp.x) - 0.5);


//		printf("tl: %d\n", tl);

		//new one:

		tmp.img_data[i] = bilin_interpol(tab->img, tl,\
							(x - 0.5) - f_x, (y - 0.5) -\
							f_y);

//		printf("color: %d\n", tmp.img_data[i]);

		
//		printf("alt test 4.5\n");

//		tmp.img_data[i] = bilin_interpol(mlx->img, &tmp, i);
//		tmp.img_data[i] = 0xF11FFF;
//		printf("color: %d\n", tmp.img_data[i]);
		++i;
	}
	printf("test 1\n");
	mlx_destroy_image(mlx->ptr, mlx->img->img_ptr);

	mlx->img = &tmp;
	
	mlx_clear_window(mlx->ptr, mlx->win_ptr);
//	mlx_put_image_to_window(mlx->ptr, mlx->win_ptr,\
		mlx->img->img_ptr, 50, 50);

//	printf("alt test 5\n");

	// seems like all that needs to be cleared gets cleard, have to test...


}

