NAME = fdf

FLAGS = -Wall -Werror -Wextra

LIBS = libs/minilibx_macos/libmlx.a\
       libs/libft/libft.a

SRCS = fdf_main.c

OBJS = $(SRCS:.c=.o)

INC = includes/

FRAMEWORKS = -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME):
	@make -C libs/libft/
	@make -C libs/minilibx_macos/
	@gcc $(FLAGS) $(SRCS) -I$(INC) $(LIBS) $(FRAMEWORKS) -o $(NAME)

clean:
	@/bin/rm -f rm $(OFILES)
	@make -C libs/libft/ clean
	@make -C libs/minilibx_macos/ clean

fclean: clean
	@/bin/rm -f rm $(NAME)
	@make -C libs/libft/ fclean
	@make -C libs/minilibx_macos/ fclean

new:
	@/bin/rm -f rm $(NAME)
	@gcc $(FLAGS) $(SRCS) -I$(INC) $(LIBS) $(FRAMEWORKS) -o $(NAME)

debug:
	@/bin/rm -f rm $@
	@gcc -g $(FLAGS) $(SRCS) -I$(INC) $(LIBS) $(FRAMEWORKS) -o $@

re: fclean all
