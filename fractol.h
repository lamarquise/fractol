/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 16:31:12 by erlazo            #+#    #+#             */
/*   Updated: 2019/07/04 19:09:14 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include "libft.h"
# include <math.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct	s_fract
{
	void	*ptr;
	void	*win_ptr;
	int		win_width;
	int		win_height;
	int		last_pix;
	void	*img_ptr;
	int		*img_data;
	int		bpp;
	int		endian;



	int		max_iter;



}				t_fract;



#endif
