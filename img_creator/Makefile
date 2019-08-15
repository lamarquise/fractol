


NAME =	img

SRC_PATH = src/
SRC_NAME =	ft_draw.c			\
			ft_initimg.c		\
			ft_img.c			\
			ft_keyhooks.c		\
			ft_zoom.c			\
			ft_interpolation.c	\
			main.c

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))

OBJ_PATH = obj/
OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))

INC = -I ~/Documents/42/z_old_projects/libft -I /usr/local/include -I include
HEADER = include/img.h
LIB_PATH = -L ~/Documents/42/z_old_projects/libft -L /usr/local/lib
LIB = -lft -lmlx
FW = -framework OpenGL -framework AppKit


CC = clang
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
#	make -C libft
	$(CC) -o $@ $^ $(LIB_PATH) $(LIB) $(FW)

$(OBJ_PATH)%.o : $(SRC_PATH)%.c $(HEADER)
	@mkdir -p $(OBJ_PATH)
	$(CC)  $(INC) -o $@ -c $<

clean:
#	make clean -C libft
	rm -rf $(OBJ_PATH)

fclean: clean
#	make fclean -C libft
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
