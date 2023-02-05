/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 21:04:21 by pcovalio          #+#    #+#             */
/*   Updated: 2023/02/05 08:54:38 by pcovalio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <limits.h>

/**
 * @brief {FAIL == -1, SUCCESS == 0}
 */
typedef enum e_return {
	FAIL=-1,
	SUCCESS
}	t_return;

typedef enum e_bool {
	false,
	true
}	t_bool;

typedef enum e_len_mod {
	NO_MOD,
	L,
	l,
	ll,
	h,
	hh
}	t_len_mod;

typedef enum e_flags {
	NO_FLAG,
	HASH = '#',
	ZERO = '0',
	MINUS = '-',
	SPACE = ' ',
	PLUS = '+',
	SEP = '\''
}	t_flags;

# define CONVERSIONS "cspdiouxXfFaAeEgG%"

typedef union u_val {
	long double		f128;
	double			f64;
	void			*ptr;
	uint64_t		u64;
	uint32_t		u32;
}					t_val;

/**
 * @brief Resulting string
 * 
 * @param s char*, c-string
 * @param len size_t, length of string
 */
typedef struct s_res {
	char			*s;
	size_t			len;
}					t_res;

typedef struct s_node {
	t_res			res;
	t_val			v;
	uint32_t		width;
	uint32_t		prcsn;
	char			flags[4];
	t_len_mod		ln_md;
	uint8_t			conv;
	t_bool			is_prcsn_def;
	struct s_node	*next;
}					t_node;

/* ****************************************************************************
 * HELPER FUNCTIONS
 *************************************************************************** */

/**
 * @brief Allocate memory and set it to zeroes
 * 
 * @param size size of allocated memory area
 * @return void* pointer to the memory
 */
void		*ft_memalloc(size_t size);

/**
 * @brief Allocate a null-terminated string filled with character c
 * 
 * @param c character to fill the string
 * @param size length of string without counting ending null-byte
 * @return char* allocated string or NULL on error
*/
char		*ft_stralloc(char c, size_t size);

/**
 * @brief Join plain and converted chunks into a single allocated return_string
 * 
 * @param return_string char**, address of the resulting string
 * @param total_bytes int, size in bytes of memory to be allocated for the result
 * @param chunks_list t_node*, list of plain and converted chunks
 * @return t_return SUCCESS or FAIL
 */
t_return	join_results(char **return_string, int total_bytes, \
						t_node *chunks_list);

/**
 * @brief Release conversion list and each node's content
 * 
 * @param chunks_list t_node*, list of plain and converted chunks
 * @return t_return SUCCESS or FAIL
 */
t_return	release_conversions(t_node *chunks_list);

/**
 * @brief Convert data from the chunks list into string chunks and store total
 * 		bytes amount
 * 
 * @param total_bytes int*, total bytes in all resulting string chunks
 * @param chunks_list t_node*, list of plain and converted chunks
 * @return t_return SUCCESS (0) or FAIL (-1)
 */
t_return	handle_conversions(int *total_bytes, t_node *chunks_list);

/**
 * @brief Allocates (with malloc(3)) and returns a string representing the 
  		integer received as an argument with required base.
 * 
 * @param n int64_t, number for conversion
 * @param base int, select base of number, must be in range 2 <= base <= 36
 * @param upper_case bool, select lower (0) or upper (1) case for character set
 * @param grp_thsnd int8_t group thousands with provided character if base == 10
 * @return char*, string on success or NULL on error. Example:
    decimal 31 == binary 11111 == octal 38 == hex 1f
 */
char		*lltoa_base(int64_t n, int base, t_bool upper_case, \
						int8_t grp_thsnd);

/**
 * @brief Allocates (with malloc(3)) and returns a string representing the 
  		unsigned integer received as an argument with required base.
 * 
 * @param n uint64_t, number for conversion
 * @param base int, select base of number, must be in range 2 <= base <= 36
 * @param upper_case bool, select lower (0) or upper (1) case for character set
 * @param grp_thsnd int8_t group thousands with provided character if base == 10
 * @return char*, string on success or NULL on error. Example:
    decimal 31 == binary 11111 == octal 38 == hex 1f
 */
char		*ulltoa_base(uint64_t n, int base, t_bool upper_case, \
						int8_t grp_thsnd);

/**
 * @brief Allocates (with malloc(3)) and returns a string representing the 
  		80-bit floating point number received as an argument with required base.
 * @param n long double, number for conversion
 * @param base int, select base of number, must be in range 2 <= base <= 36
 * @param upper_case bool, select lower (0) or upper (1) case for character set
 * @param prec uint64_t, number of decimal digits to be printed
 * @return char*, string on success or NULL on error. Example:
    decimal 31 == binary 11111 == octal 38 == hex 1f
*/
char		*dbltostr_base(long double n, int base, t_bool upper, \
						uint64_t prec);

/**
 * @brief Join n heap-allocated strings and free them, NULL is ignored
 * 
 * @param n amount of parameters
 * @param ... char* string pointers
 * @return char* string on success, NULL on error
 */
char		*string_joiner(size_t n, ...);

/**
 * @brief Gather all conversion-related info (flags, width, precision, 
 * 		length modifiers) into t_node and move address of fmt-string
 * 		to the byte after conversion character
 * 
 * @param tmp t_node*, structure to store all conversion-related data
 * @param fmt char**, address of format-string
 * @return t_return SUCCESS or FAIL
 */
t_return	parse_conversion(t_node *tmp, const char **fmt);

/**
 * @brief Parse format-string and store all conversion-related data in a list
 * 
 * @param head t_node**, address of pointer to store list of all conversions
 * @param fmt char*, format-string
 * @param ap va_list, list of arguments whose number and types are not known
 * @return t_return SUCCESS or FAIL
 */
t_return	parse_format(t_node **head, const char *fmt, va_list ap);

#endif
