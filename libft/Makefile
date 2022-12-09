# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/28 17:38:49 by pcovalio          #+#    #+#              #
#    Updated: 2022/12/08 19:33:26 by pcovalio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libft.a

CFLAGS=-Wall -Wextra -Werror -pedantic -o3

AR=ar -rc

HDR=include
OBJDIR=obj
SRCDIR=src

SRC= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
	ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c \
	ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c \
	ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c \
	ft_tolower.c ft_toupper.c ft_lstadd_back.c ft_lstdelone.c ft_lstmap.c \
	ft_lstadd_front.c ft_lstiter.c ft_lstnew.c ft_lstclear.c ft_lstlast.c \
	ft_lstsize.c 

OBJ=$(SRC:%.c=$(OBJDIR)/%.o)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p '$(@D)'
	$(CC) $(CFLAGS) -I$(HDR) -c $< -o $@

all:$(NAME)

$(NAME):$(OBJ)
	$(AR) $(NAME) $^

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)
	rm -f test

re: fclean all

.PHONY: all clean fclean re bonus
