NAME=libftprintf.a

CFLAGS=-Wall -Wextra -Werror -pedantic $(BONUSFLAG) -g3

AR=ar -rc

BONUSFLAG=
BSUF=
HDR=-Iinclude -Ilibft/include
OBJDIR=obj
SRCDIR=src

SRC= manage_memory.c ft_ntoa_base.c ft_printf.c string_joiner.c \
	ft_dbltostr_base.c parse_format.c parse_format_utils.c \
	handle_conversions.c handle_conversions_utils.c

BSRC = 

OBJ=$(SRC:%.c=$(OBJDIR)/%.o)

BOBJ=$(BSRC:%.c=$(OBJDIR)/%.o)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p '$(@D)'
	$(CC) $(CFLAGS) $(HDR) -c $< -o $@

all: $(NAME)
$(NAME):$(OBJ)
	make all -C libft
	$(AR) $(NAME) $^ libft/libft.a

bonus: BONUSFLAG=-DBONUS
BSUF=_bonus

bonus: $(OBJ) $(BOBJ)
	make all -C libft
	$(AR) $(NAME) $^

clean:
	make clean -C libft
	rm -rf $(OBJDIR)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)
	rm -f test

so:
	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRC) $(BSRC)
	gcc -nostartfiles -shared -o libft.so $(OBJ) $(BOBJ)

re: fclean all

test: all
	@$(CC) -I$(HDR) -c tests/main.c -o obj/main.o
	@$(CC) -o test obj/main.o libftprintf.a libft/libft.a

.PHONY: all clean fclean re bonus
