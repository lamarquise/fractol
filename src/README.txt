
FRACTOL README

not quite complete, but in the works and a good reference

have yet to explain the zoom and redraw parts...


Fractol.h:

t_fract
	var called is *mlx
	contains generic mlx info for later use
	and a table of t_ol

t_ol:
	var called is *tab, there is one for each window
	contains mlx info for particular window and fractal
	and a t_orig

t_orig:
	var called is *cent
	contains fractal projection info and dimentions





Main.c:

main:
	Calls funcs that pars the ac av
	then calls ft_fractal

ft_inp_n_fill:
	compars av input to possible valid inputs and stores in a list



Ft_fractal.c:

ft_fractal:
	init mlx and tab vars
	calls ft_initfractal
	calls ft_draw for each elem of tab (ie each requested window)
	calls and manages ft_hooks_loop with mlx_loop

ft_clear_mlx:
	clears everythign from every open window and then closes all windows	???

ft_quitone
	clears and quits a single window	???

ft_quitfract
	calls ft_clear_mlx
	exits
	ultimate exit of program.



Ft_initfractal.c:

ft_initfractal:
	calls ft_createwin for each elem of tab, (to create a window for each)

ft_creatwin:
	inits all var in iteration of t_ol struct var, with all base values
	creates the windown and attaches img to it



Ft_draw.c:

ft_draw:
	for each pixel, calculates pos in complex plane (based on size of win and stuff)
	calls ft_math_it for each pix, sending struct var t_compn (2 doubles)
	applied color to each pix
	calls ft_drawcoordsys	(name sais it all)

ft_math_it:
	repeats mendelbrot calculation until solution or reaches max
	returns result...?







