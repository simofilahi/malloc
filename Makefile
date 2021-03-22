
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
	  srcs/calloc.c\
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
	  srcs/libft_func/ft_bzero.c\
	  srcs/mem_zone.c\
	  srcs/mini_printf.c\

PTHREAD_LIB = -lpthread

BoldRed = \033[1;31m
BoldGreen = \033[1;32m
BoldBlue = \033[1;34m
BoldYellow = \033[01;33m
ED = \033[0m

OBJS = $(SRCS:.c=.o)

all: $(HOST) $(NAME)

$(NAME): $(OBJS)
	@echo "$(BoldGreen)LIBRARY CREATION$(ED)"
	@gcc -shared -o $(NAME) -I includes/. $(OBJS) $(PTHREAD_LIB)
	@echo "$(BoldGreen)SYMBOLIC LINK CREATION$(ED)"
	@ln -s $(NAME) $(SYMB)
	@echo "$(BoldGreen)DONE$(ED)"

%.o: %.c
	@echo "$(BoldBlue)COMPILING SRCS...$(ED)"
	@$(CC) $(CFLAG) -fPIC -c $< -o $@
	
clean:
	@echo "$(BoldYellow) REMOVE OBJECTS"
	@rm -rf $(OBJS)

fclean: clean
	@echo "$(BoldYellow) REMOVE LIBRARY AND SYMBOLIC LINK"
	@rm -rf $(NAME) $(SYMB)


help:
	@echo "SRCS = $(SRCS)"
	@echo "OBJS = $(OBJS)"
	@echo "HOST = ${HOSTTYPE}"