CC = cc -g
CFLAGS = -I./lib/libft -I/usr/include -I./lib/minilibx -O3 #-fsanitize=address -g
MLXFLAGS = -L./lib/minilibx -lmlx -L/usr/lib -lXext -lX11 -lm -lz
NAME = cub3D

# Libft kaynak dosyalarını buraya ekledik
LIBFT_SRCS = lib/libft/ft_strlen.c lib/libft/ft_memmove.c lib/libft/ft_strlcpy.c \
	lib/libft/ft_strlcat.c lib/libft/ft_isalpha.c lib/libft/ft_isdigit.c \
	lib/libft/ft_isalnum.c lib/libft/ft_isascii.c lib/libft/ft_isprint.c \
	lib/libft/ft_memset.c lib/libft/ft_bzero.c lib/libft/ft_toupper.c \
	lib/libft/ft_tolower.c lib/libft/ft_strchr.c lib/libft/ft_strrchr.c \
	lib/libft/ft_strncmp.c lib/libft/ft_memchr.c lib/libft/ft_memcmp.c \
	lib/libft/ft_strnstr.c lib/libft/ft_atoi.c lib/libft/ft_calloc.c \
	lib/libft/ft_strdup.c lib/libft/ft_substr.c lib/libft/ft_strjoin.c \
	lib/libft/ft_strtrim.c lib/libft/ft_split.c lib/libft/ft_itoa.c \
	lib/libft/ft_strmapi.c lib/libft/ft_striteri.c lib/libft/ft_putchar_fd.c \
	lib/libft/ft_putstr_fd.c lib/libft/ft_putendl_fd.c lib/libft/ft_putnbr_fd.c \
	lib/libft/get_next_line.c lib/libft/ft_lstnew.c lib/libft/ft_lstadd_front.c \
	lib/libft/ft_lstsize.c lib/libft/ft_lstlast.c lib/libft/ft_lstadd_back.c \
	lib/libft/ft_lstiter.c lib/libft/ft_lstdelone.c lib/libft/ft_lstmap.c \
	lib/libft/ft_memcpy.c lib/libft/ft_lstclear.c

SRCS = main.c src/parser/fill_struct.c src/parser/init.c src/utils/parser_utils.c \
	src/utils/parser_utils2.c src/checker/flood_fill_v1.c src/checker/image_checker.c \
	src/cleanup/clean_up.c src/checker/flood_fill_v2.c src/checker/flood_fill_v1_2.c \
	$(LIBFT_SRCS) src/executor/mlx.c src/parser/player.c src/checker/image_checker_2.c \
	src/parser/map_init.c src/parser/map_utils.c src/parser/texture_handlers.c \
	src/parser/texture_processing.c src/parser/player_dir.c src/executor/render.c \
	src/executor/render_rotate.c src/executor/display.c src/executor/ray.c \
	src/executor/init_mlx.c

OBJS = $(SRCS:.c=.o)

MLX_DIR = lib/minilibx
MLX = $(MLX_DIR)/libmlx.a

all: $(NAME)

$(NAME): $(OBJS) $(MLX)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLXFLAGS)

$(MLX):
	make -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(MLX_DIR)/libmlx.a

re: fclean all

.PHONY: all clean fclean re
