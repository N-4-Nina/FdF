# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abouchau <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/05 16:42:52 by abouchau          #+#    #+#              #
#    Updated: 2020/10/05 13:17:02 by chpl             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = FdF
LIBFT = libft
OS	= $(shell uname)
DIR_S = srcs
INCLUDES = -I includes/ -I libft/ -I $(MLX_DIR) -I get_next_line/
CC = clang
CFLAGS	= -O3 -Wall -Wextra -Werror
LIBS	= -L libft/ -lft ${MLX_LNK} -lm
GNLBUFF = -D BUFFER_SIZE=1000
SOURCES =  srcs/FdF.c \
			srcs/utils.c \
			srcs/draw_mesh.c \
			srcs/colors.c \
			srcs/hooks.c \
			srcs/loop.c \
			srcs/exit.c \
			srcs/parser.c \
			srcs/init.c \
			srcs/commands.c \
			srcs/rotate.c \
			srcs/project.c

OBJS	= ${SOURCES:.c=.o}

ifeq ($(OS), Linux)
	MLX_DIR	= linux/minilibx-linux/
	MLX_LNK	= -L ${MLX_DIR} -lmlx -lXext -lX11 -lbsd
	SOURCES += linux/get_next_line.c
else
	MLX_DIR	= osx/minilibx_opengl
	MLX_LNK	= -L ${MLX_DIR} -lmlx -framework OpenGL -framework AppKit
	SOURCES += osx/get_next_line.c
endif

.c.o:
	${CC} ${CFLAGS} ${GNLBUFF} -c $< -o ${<:.c=.o} ${INCLUDES}

all : $(NAME)

${NAME}: ${OBJS}
	@make -C libft
	@make -C ${MLX_DIR}
	${CC} ${CFLAGS} ${INCLUDES} ${OBJS} ${LIBS} -o ${NAME}

$(DIR_O)/%.o: $(DIR_S)/%.c $(HEADER)/*.h
	@mkdir -p objs
	@$(CC) $(CFLAGS) -I $(HEADER) -o $@ -c $<
clean :
	@rm -f $(OBJS)
	@make clean -C $(LIBFT)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)

re: fclean all

.PHONY:	clean fclean all re mlx ft
