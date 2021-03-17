NAME = malloc
CC = gcc
CFLAG = -Wextra -Werror -Wall
SRCS = srcs/free.c\
 	  srcs/realloc.c\
	  srcs/malloc.c\
	  srcs/show_alloc_mem.c\
	  srcs/malloc_helper.c\
	  srcs/free_helper.c\
	  main.c
LIBS = libft/libft.a

OBJS = $(SRCS:%.c=%.o)
	

all: $(NAME)

$(NAME): $(OBJS)
		@$(CC) $(CFLAG) $(OBJS) $(LIBS) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAG) -c $< -o $@

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

help:
	@echo "SRCS = $(SRCS)"
	@echo "OBJS = $(OBJS)"