CC = cc
CFLAGS = -Wall -Wextra -Werror -c\
		-I$(INCDIR) -I$(LIBFTDIR) -I$(LINALGDIR)/include\
		-I$(DYNARRDIR)/include -I$(MLX42DIR)/include

NAME = fdf

SRCFILES = FdF.c edges.c verteces.c model.c load_map.c\
		   draw_line.c draw_map.c draw_utils.c to_hsv.c to_rgb.c
SRCDIR = src
SRCS = $(addprefix $(SRCDIR)/, $(SRCFILES))

OBJFILES = $(SRCFILES:.c=.o)
OBJDIR = obj
OBJS = $(addprefix $(OBJDIR)/, $(OBJFILES))

LIBFTDIR = ./libft
LINALGDIR = ./ft_linalg
DYNARRDIR = ./ft_dynarr
MLX42DIR = MLX42

LIBDIR = lib

INCDIR = include

.PHONY: all clean fclean re run debug


all: CFLAGS += -O3
all: $(NAME)

$(NAME): $(OBJS) $(LIBDIR)/libft.a $(LIBDIR)/libft_linalg.a\
	$(LIBDIR)/libftdynarr.a $(LIBDIR)/libmlx42.a
	$(CC) $(OBJS) -o $(NAME) -L$(LIBDIR) -lftdynarr -lft_linalg -lft -lmlx42\
		-ldl -lglfw -pthread -lm

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(LIBFTDIR)/libft.h\
	$(LINALGDIR)/include $(DYNARRDIR)/include $(MLX42DIR)/include | $(OBJDIR)
	$(CC)	$(CFLAGS) -o $@ $<

$(LIBFTDIR)/libft.h $(LIBDIR)/libft.a: | $(INCDIR) $(LIBDIR)
	@ git submodule update --init --recursive libft
	@ cd $(LIBFTDIR) && git switch inc_math
	@ make -C $(LIBFTDIR) all
	@ cd $(LIBDIR) && ln -sf ../$(LIBFTDIR)/libft.a

$(LINALGDIR)/include $(LIBDIR)/libft_linalg.a: | $(LIBDIR)
	@ git submodule update --init --recursive ft_linalg
	@ make -C $(LINALGDIR) LIBFTDIR="../libft"
	@ cd $(LIBDIR) && ln -sf ../$(LINALGDIR)/libft_linalg.a

$(DYNARRDIR)/include $(LIBDIR)/libftdynarr.a: | $(LIBDIR)
	@ git submodule update --init --recursive ft_dynarr
	@ make -C $(DYNARRDIR) LIBFTDIR="../libft"
	@ cd $(LIBDIR) && ln -sf ../$(DYNARRDIR)/libftdynarr.a

$(MLX42DIR)/include $(LIBDIR)/libmlx42.a: |$(LIBDIR)
	@ git submodule update --init --recursive MLX42
	@ cd $(MLX42DIR) && cmake -B build && cmake --build build -j8
	@ cd $(LIBDIR) && ln -sf ../$(MLX42DIR)/build/libmlx42.a

$(OBJDIR):
	@ mkdir -p $(OBJDIR)

$(LIBDIR):
	@ mkdir -p $(LIBDIR)

$(INCDIR):
	@ mkdir -p $(INCDIR)

clean:
	@ rm -rfv $(OBJDIR)

fclean: clean
	@ rm -v $(NAME)

re: clean all

debug: CFLAGS += -gdwarf-2 -O0
debug: $(NAME)

run: all
	@ clear
	@ echo "############# RUNNING $(NAME) #############"
	@ ./$(NAME) ./test_maps/10-2.fdf
