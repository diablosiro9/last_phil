# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/25 14:59:45 by dojannin          #+#    #+#              #
#    Updated: 2022/11/12 22:22:25 by dojannin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

OBJ = $(SRCS:.c=.o)

CFLAGS += -Wall -Wextra -Werror -g -fsanitize=address -pthread

SRCS = 	main.c \
		
%.o: %.c
	$(CC) -Wall -Wextra -Werror -c $< -o $@
	
$(NAME):		$(OBJ)
					$(CC) $(CFLAGS) $(OBJ) -o $(NAME) 

bonus:		$(OBJBONUS)
	$(CC) $(CFLAGS) $(OBJBONUS) -o $(NAME) 

all:			$(NAME)

clean:			
				rm -f $(OBJ)

fclean:			clean
					rm -f $(NAME)

norme:
					norminette -R CheckForbiddenSourceHeader $(SRCS) 

re:				fclean all

.PHONY :		all clean fclean re
