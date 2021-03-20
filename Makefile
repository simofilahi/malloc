
NAME = libft_malloc_$(HOSTTYPE).so

HOST = 
ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

SYMB = libft_malloc.so

CC = gcc
CFLAG = -Wextra -Werror -Wall
SRCS = srcs/free.c\
 	  srcs/realloc.c\
	  srcs/malloc.c\
	  srcs/show_alloc_mem.c\
	  srcs/show_alloc_mem_ex.c\
	  srcs/malloc_helper.c\
	  srcs/free_helper.c\
	  srcs/libft_func/ft_memcpy.c\
	  srcs/libft_func/ft_putchar.c\
	  srcs/libft_func/ft_putendl.c\
	  srcs/libft_func/ft_strlen.c\
	  srcs/libft_func/ft_putstr.c\
	  srcs/libft_func/ft_putnbr.c\
	  srcs/show_alloc_mem_ex.c\
	  srcs/mem_zone.c\
	  srcs/mini_printf.c\

PTHREAD_LIB = -lpthread

OBJS = $(SRCS:%.c=%.o)
	
all: $(HOST) $(NAME)

$(NAME): $(OBJS)
		@ar rc $(NAME) $(OBJS) 
		@ln -s $(NAME) $(SYMB)

%.o: %.c
	@$(CC) $(CFLAG) -c $< -o $@
	
clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME) $(SYMB)


help:
	@echo "SRCS = $(SRCS)"
	@echo "OBJS = $(OBJS)"
	@echo "HOST = ${HOSTTYPE}"