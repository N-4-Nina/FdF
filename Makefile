NAME = FdF
LIBFT = libft
OS	= $(shell uname)
DIR_S = srcs
INCLUDES = -I includes/ -I libft/ -I $(MLX_DIR) -I get_next_line/
CC = clang
CFLAGS	= -O3 -Wall -Wextra -Werror
LIBS	= -L libft/ -lft ${MLX_LNK} -lm
GNLBUFF = -D BUFFER_SIZE=100
SOURCES =  srcs/FdF.c 

OBJS	= ${SOURCES:.c=.o}

ifeq ($(OS), Linux)
	MLX_DIR	= linux/minilibx-linux/
	MLX_LNK	= -L ${MLX_DIR} -lmlx -lXext -lX11 -lbsd
	SOURCES += linux/get_next_line.c
	INCLUDES += -I linux/
else
	MLX_DIR	= osx/minilibx
	MLX_LNK	= -L ${MLX_DIR} -lmlx -framework OpenGL -framework AppKit
	SOURCES += osx/get_next_line.c
	INCLUDES += -I osx/
endif

.c.o:
	${CC} ${CFLAGS} ${GNLBUFF} -c $< -o ${<:.c=.o} ${INCLUDES}

all : $(NAME)

${NAME}: ${OBJS} ft mlx
		${CC} ${CFLAGS} ${INCLUDES} ${OBJS} ${LIBS} -o ${NAME}

mlx:
	@make -C $(MLX_DIR)

ft:
	@make -C libft

$(DIR_O)/%.o: $(DIR_S)/%.c $(HEADER)/*.h
	@mkdir -p objs
	@$(CC) $(CFLAGS) -I $(HEADER) -o $@ -c $<
clean :
	@rm -f $(OBJS)
	@make clean -C $(LIBFT)
	@make clean -C $(MLX_DIR)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)
	@make clean -C $(MLX_DIR)

re: fclean all

.PHONY:	clean fclean all re mlx ft
