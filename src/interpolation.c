


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

void	ft_resize(t_ol *tab)
{
	t_mag	tmp;

	int		img_st_x;		// x pos of top left of img in wind, unit is  pixels, (0,0) is top left
	int		img_st_y;		// aka the number of pixels between the top left of window and top left of img
	double	tmp_scale;
	double	relative_x;
	double	relative_y;
	int		n_of_interpolations;
	int		i;
	int		iter;
	int		tl;		// in pixels, relative to tl of window, mot 2D coordinate pixels, just the int *tab pixels


	if (!(tmp.img_ptr = mlx_new_image(tab->mlx->ptr, tab->win_width, tab->win_height)))
		return ;
//	if (!(
	tmp.img_data = (int*)mlx_get_data_addr(tmp.img_ptr,\
		&tab->mlx->bpp, &tab->mlx->s_l, &tab->mlx->endian); //))
//		return ;

	printf("inter 1\n");

	iter = 1;
	n_of_interpolations = 2; // actually its number of interpolations + 1
	while (iter < n_of_interpolations)
	{

		printf("st_y: %f\n", tab->st_y);

		tmp_scale = ((tab->old_scale - tab->scale) /\
					n_of_interpolations) * iter + tab->scale;
		// or - old_scale, how to make this zoom in AND out ???

		tmp.x = (tab->old_wid_scale - tab->wid_scale) /\
				n_of_interpolations * iter / tab->old_scale;

		tmp.y = ((tab->old_hei_scale - tab->hei_scale) /\
				n_of_interpolations) * iter / tab->old_scale;

		printf("tmpx: %d, tmpy: %d\n", tmp.x, tmp.y);

		tmp.last_p = tmp.x * tmp.y;

		img_st_x = ((tab->old_st_x - tab->st_x) / n_of_interpolations) *\
					iter / tab->old_scale;	// also iteration compatible
		img_st_y = ((tab->old_st_y - tab->st_y) / n_of_interpolations) *\
					iter / tab->old_scale;

		printf("last p: %d\n", tmp.last_p);

		i = 0;
		while (i < tab->last_pix)
		{
//			printf("inter 4\n");

			relative_x = (tmp.x / tab->win_width) *\
						(double)(i % tab->win_width);

			relative_y = (tmp.y / tab->win_height) *\
						((double)i / tab->win_height);

			tl = img_st_x + tab->win_width * img_st_y +\
				(floor(relative_x - 0.5) + floor(relative_y - 0.5) *\
				tab->win_width);

			tmp.img_data[i] = bilin_interpol(&tmp, tl,(relative_x - 0.5) -\
							(floor(relative_x - 0.5)), (relative_y - 0.5) -\
							(floor(relative_y - 0.5)));
			
//			printf("color: %d\n", tmp.img_data[i]);
			
			++i;
		}
		mlx_clear_window(tab->mlx->ptr, tab->win_ptr);
		mlx_put_image_to_window(tab->mlx->ptr, tab->win_ptr,\
								tmp.img_ptr, 0, 0);
	
		++iter;
	}

	printf("inter 5\n");

}





/*



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

*/

