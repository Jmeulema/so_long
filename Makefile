# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmeulema <jmeulema@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/16 17:42:28 by jmeulema          #+#    #+#              #
#    Updated: 2022/11/15 16:22:52 by jmeulema         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

RM = rm -rf
CC = gcc
FLAGS = -Wall -Wextra -Werror

SRCSDIR = Srcs
OBJSDIR = Objs
INCSDIR = Includes

INC = \
		so_long.h \
			
SRC = \
			basic_commands.c \
			ft_strncmp.c \
			get_next_line_utils.c \
			get_next_line.c \
			init.c \
			map.c \
			move.c \
			parse_input.c \
			put_elements.c \
			so_long.c \
			so_long_utils.c \
			win.c \
	
SRCS = $(addprefix $(SRCSDIR)/, $(SRC))
OBJS = $(addprefix $(OBJSDIR)/, $(addsuffix .o, $(basename $(SRC))))
OBJS_DIR = $(sort $(dir $(OBJS)))

INCS_DIR = $(addsuffix /, $(INCSDIR))
INCS = $(addprefix -I , $(INCS_DIR))

MLX_INC = -I minilibx
MLX_LIB = minilibx/libmlx.a
MLX_LINK = -L minilibx -l mlx -framework OpenGL -framework AppKit

all : $(NAME) $(MLX_LIB)

$(NAME) : mlx $(OBJS)
	$(CC) $(OBJS) $(MLX_LINK) -lm -o $(NAME)

mlx :
	@make -C minilibx

clean :
		$(RM) $(OBJS_DIR)
		$(RM) $(OBJSDIR)
		make -C minilibx clean

fclean : clean 
		$(RM) $(NAME)

re : fclean all

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c
		mkdir -p $(OBJSDIR) $(OBJS_DIR)
		$(CC) -c $< $(MLX_INC) $(INCS) $(FLAGS) -o $@
