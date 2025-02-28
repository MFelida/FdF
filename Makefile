CC = cc
CFLAGS = -Wall -Wextra -Werror -c -I$(INCDIR) -I$(LIBFTDIR) -I$(LINALGDIR)

NAME = FdF

SRCFILES = FdF.c
SRCDIR = src
SRCS = $(addprefix $(SRCDIR)/, $(SRCFILES))

OBJFILES = $(SRCFILES:.c=.o)
OBJDIR = obj
OBJS = $(addprefix $(OBJDIR)/, $(OBJFILES))

LIBFTDIR = ./libft
LINALGDIR = ./ft_linalg

LIBDIR = lib

INCDIR = include

.PHONY: all clean fclean re run

all: $(NAME)

$(NAME): $(OBJS) $(LIBDIR)/libft.a $(LIBDIR)/libft_linalg.a
	$(CC) $(OBJS) -o $(NAME) -L$(LIBDIR) -lft_linalg -lft -lm

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(LIBFTDIR)/libft.h\
	$(LINALGDIR)/include | $(OBJDIR)
	$(CC)	$(CFLAGS) -o $@ $< 

$(LIBFTDIR)/libft.h $(LIBDIR)/libft.a: | $(INCDIR) $(LIBDIR)
	@ git submodule update --init --recursive
	@ make -C $(LIBFTDIR) all
	@ cd $(LIBDIR) && ln -sf ../$(LIBFTDIR)/libft.a

$(LINALGDIR)/include $(LIBDIR)/libft_linalg.a: | $(LIBDIR)
	@ git submodule update --init --recursive ft_linalg
	@ make -C $(LINALGDIR) LIBFTDIR="../libft"
	@ cd $(LIBDIR) && ln -sf ../$(LINALGDIR)/libft_linalg.a

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

re: fclean all

run: all
	@ echo "############# RUNNING $(NAME) #############"
	@ ./$(NAME)
