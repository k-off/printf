NAME=libftprintf.a

CFLAGS=-Wall -Wextra -Werror -pedantic $(BONUSFLAG)

AR=ar -rc

BONUSFLAG=
BSUF=
HDR=-Iinclude -Ilibft/include
OBJDIR=obj
SRCDIR=src

SRC= ft_printf.c

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

test: bonus
	@$(CC) -I$(HDR) -c tests/main.c -o tests/main.o
	@$(CC) -o test tests/main.o libft.a
	./test

.PHONY: all clean fclean re bonus
