# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: feedme <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/01 01:00:24 by feedme            #+#    #+#              #
#    Updated: 2019/05/01 01:00:35 by feedme           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl

FLAGS = -Wall -Wextra -Werror

SRC = srcs/*.c

all: $(NAME)

$(NAME):
		gcc $(FLAGS) $(SRC) -o $(NAME) libft.a libftprintf.a -g
clean:
	rm -rf *.o $(NAME).dSYM

fclean: clean
	rm -rf $(NAME) $(NAME).dSYM

re: fclean all
