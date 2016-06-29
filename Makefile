# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amerelo <amerelo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/24 14:23:47 by amerelo           #+#    #+#              #
#    Updated: 2016/06/29 04:04:19 by amerelo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

DIR_H = ./inc/

DIR_C = ./src/

DIR_O = ./objs/

FILE_C = main.c init.c envent.c tools.c frac_1.c frac_2.c

FILE_O = $(FILE_C:.c=.o)

SRC_C := $(addprefix $(DIR_C), $(FILE_C))

SRC_O := $(addprefix $(DIR_O), $(FILE_O))

FLAGS = -Wall -Wextra -Werror -O3 -march=native

all: $(NAME)

$(NAME): $(SRC_O)
	@gcc -o $(NAME) $(SRC_O) -L libft/ -lft -lmlx -framework OpenGL -framework AppKit

$(SRC_O): $(SRC_C)
	@make -C libft/
	@clang $(FLAGS) -c $(SRC_C) -I $(DIR_H) -I minilibx_macos/
	@mkdir -p $(DIR_O)
	@mv $(FILE_O) $(DIR_O)

clean:
	@/bin/rm -rf $(DIR_O)
	@make clean -C libft/

fclean: clean
	@/bin/rm -f $(NAME)
	@make fclean -C libft/

re: fclean all

.PHONY: clean fclean all re
