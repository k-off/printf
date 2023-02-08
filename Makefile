# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/08 17:11:15 by pcovalio          #+#    #+#              #
#    Updated: 2023/02/08 18:09:31 by pcovalio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a
INCLUDE		= include
LIBFT		= libft
SRC_DIR		= src/
OBJ_DIR		= obj/
CFLAGS		= -Wall -Wextra -Werror -pedantic -o3
RM			= rm -f
AR			= ar rcs

#Sources

SRC_FILES	=	manage_memory ft_ntoa_base ft_printf string_joiner \
	ft_dbltostr_base parse_format parse_format_utils \
	handle_conversions handle_double_conversion handle_string_conversion \
	handle_integer_conversion handle_double_utils handle_integer_utils

SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

###

OBJF		=	.cache_exists

all:		$(NAME)

$(NAME):	$(OBJ)
			@make -C $(LIBFT)
			@cp libft/libft.a .
			@mv libft.a $(NAME)
			@$(AR) $(NAME) $(OBJ)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
			$(CC) $(CFLAGS) -I$(INCLUDE) -Ilibft/include -c $< -o $@

$(OBJF):
			@mkdir -p $(OBJ_DIR)

clean:
			@$(RM) -rf $(OBJ_DIR)
			@make clean -C $(LIBFT)

fclean:		clean
			@$(RM) -f $(NAME)
			@$(RM) -f $(LIBFT)/libft.a

re:			fclean all

bonus: all

.PHONY:		all clean fclean re bonus
