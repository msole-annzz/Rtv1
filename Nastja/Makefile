NAME = rtv1 

SRCS =  ./source/main.c

OB = $(SRCS:.c=.o)

FLAG = -Wall -Wextra -Werror
HEADER = includes/
LIBFT = libft/libft.a
LIBFT_PATH = libft
MINILIBX = minilibx -lmlx -framework OpenGL -framework AppKit

.PHONY: all clean clean re

all: $(NAME)
$(NAME): $(LIBFT) $(OB)
	gcc -I $(LIBFT_PATH) $(OB) -o $(NAME) -L $(LIBFT_PATH) -lft -L $(MINILIBX) -lpthread
$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)
%.o: %.c
	@gcc $(FLAG) -I $(HEADER) -c $< -o $@
clean:
	@/bin/rm -f $(OB)
	@$(MAKE) -C $(LIBFT_PATH) clean
fclean: clean
	@/bin/rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean
re: fclean all
