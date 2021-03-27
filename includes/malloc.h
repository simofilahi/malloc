/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 17:42:27 by mfilahi           #+#    #+#             */
/*   Updated: 2021/03/27 15:19:03 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
# include <unistd.h>
# include <sys/mman.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <pthread.h>

/*
 ** -MAX SIZE OF AN ALLOCATION IN A ZONE
*/

# define MAX_TINY_ZONE_SIZE 255
# define MAX_SMALL_ZONE_SIZE 4092

/*
 ** - MMAP PAGES
*/

# define TINY_ZONE_PAGES 10
# define SAMLL_ZONE_PAGES 150
# define EXTRA_ZONE_PAGES 150

/*
 ** DEFINITION OF ZONES
*/

# define TINY_ZONE 1
# define SMALL_ZONE 2
# define LARGE_ZONE 3
# define EXTRA_ZONE 4

# define SUCCESS 0
# define FAILED 1

# define TRUE 1
# define FALSE 0

/*
 ** - THREAD SAFE GLOBAL VARIABLE
*/

pthread_mutex_t			g_lock;

/*
 ** - BLOCK STRUCTURE
*/
typedef struct			s_block
{
	size_t				block_size;
	struct s_block		*next;
	size_t				used;
	size_t				alloc_size;
}						t_block;

/*
 ** - ZONE STRUCTURE
*/

typedef struct			s_mem_zone
{
	void				*start_zone;
	struct s_mem_zone	*next;
	size_t				zone_size;
	size_t				type;
	t_block				*head_block;
	t_block				*tail_block;
}						t_mem_zone;

/*
 ** FIRST ZONE
*/

t_mem_zone				*g_head_zone;

/*
 ** MEMORY ZONES
*/

void					*create_new_zone(size_t pages, size_t type);
void					add_new_zone_to_list(t_mem_zone *new_zone);
void					*create_large_zone(size_t total_size);
void					*create_extra_zone(size_t total_size);

/*
 ** - FREE FUNCTIONS
*/

void					free(void *ptr);
void					merge_block(t_mem_zone *zone, t_block *prev_block,
		t_block *curr_block);

/*
 ** - REALLOC FUNCTIONS
*/

void					*realloc(void *ptr, size_t size);

/*
 ** - REALLOCF FUNCTIONS
*/

void					*reallocf(void *ptr, size_t size);

/*
 ** - MALLOC FUNCTIONS
*/

void					*malloc(size_t size);
void					*find_free_block_in_extra_zone(size_t total_size);
void					*fill_first_block(t_mem_zone *zone, size_t total_size);
void					*fill_block(t_mem_zone *zone, size_t total_size);
void					*create_new_block_in_zone(t_mem_zone *zone,\
		size_t total_size);

/*
 ** - VISUALISATION
*/

void					show_alloc_mem(void);
void					show_alloc_mem_ex(void);

/*
 ** - PRINT FUNCTIONS
*/
void					min_printf(void *str, void *ptr, int nflag);

/*
 ** - UTILIS
*/

void					calculateblock_size(t_block *curr, size_t *block_size);

/*
 ** - LIBFT FUNCTIONS
*/
void					*ft_memcpy(void *dst, const void *src, size_t n);
void					ft_putchar(char c);
void					ft_putstr(char const *s);
void					ft_putendl(char const *s);
void					ft_putnbr(long n);
size_t					ft_strlen(const char *s);
void					ft_bzero(void *s, size_t n);
#endif
