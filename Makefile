# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imontero <imontero@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/21 16:14:07 by imontero          #+#    #+#              #
#    Updated: 2023/09/08 13:26:44 by imontero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 				pipex

NAME_BONUS = 		pipex_bonus

CC = 				gcc

CFLAGS =			-g3 -Wall -Werror -Wextra -fsanitize=address

LIBFT = 			libft.a

SRC_FILES =			pipex.c \
			 		pipex_utils.c \
					error.c \
				
SRC_FILES_BONUS = 	pipex_bonus.c \
					pipex_utils_bonus.c \
					error_bonus.c \
					
INCLUDE = 			pipex.h

INCLUDE_BONUS = 	pipex_bonus.h

OBJS = $(SRC_FILES:.c=.o)

OBJS_BONUS = $(SRC_FILES_BONUS:.c=.o)

#.c.o: $(SRCS)
#	$(CC) $(CFLAGS) $(SRCS) -c $(OBJS) -o

all: libft $(NAME)

libft:
	make -C my_libft
	cp my_libft/$(LIBFT) $(LIBFT)

$(NAME): $(OBJS) $(INCLUDE)
	$(CC) $(CFLAGS) $(OBJS) $(FTPRINTF) $(GNL) $(LIBFT) -o $(NAME)
	
$(NAME_BONUS): $(OBJS_BONUS) $(INCLUDE_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(FTPRINTF) $(GNL) $(LIBFT) -o $(NAME_BONUS)

clean:
	rm -f $(OBJS)
	rm -f $(OBJS_BONUS)
	rm -f $(LIBFT)
	make -C my_libft clean

fclean: clean
	rm -f $(NAME) 
	rm -f $(NAME_BONUS)
	make -C my_libft fclean

re: fclean all

bonus: libft $(NAME_BONUS)

.PHONY: all clean fclean re libft bonus