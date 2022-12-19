/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 21:04:21 by pcovalio          #+#    #+#             */
/*   Updated: 2022/12/18 13:36:08 by pcovalio         ###   ########.fr       */
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
	ll,
	l,
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

typedef enum e_conv {
	NO_CONV,
	c = 'c',
	s = 's',
	p = 'p',
	d = 'd',
	i = 'i',
	o = 'o',
	u = 'u',
	x = 'x',
	X = 'X',
	f = 'f',
	F = 'F',
	prc = '%'
}	t_conv;

typedef union u_val {
	long double		f128;
	double			f64;
	void			*ptr;
	uint64_t		u64;
	uint32_t		u32;
}					t_val;

typedef struct s_res {
	char			*s;
	size_t			len;
}					t_res;

typedef struct s_node {
	int32_t			width;
	int32_t			prcsn;
	t_flags			flags;
	t_len_mod		ln_md;
	t_val			v;
	t_conv			conv;
	t_res			res;
	struct s_node	*next;
}					t_node;

/**
 * @brief Write output to stdout, the standard output stream
 * 
 * @param format char*, format string
 * @param ... variable number of arguments
 * @return int negative on error, or the number of characters written
 * 			(excluding the null byte used to end output to strings)
 */
int		ft_printf(const char *format, ...);

/**
 * @brief Write output to the specified file_descriptor
 * 
 * @param file_descriptor int, file descriptor
 * @param format char*, format string
 * @param ... variable number of arguments
 * @return int negative on error, or the number of characters written
 * 			(excluding the null byte used to end output to strings)
 */
int		ft_dprintf(int file_descriptor, const char *format, ...);

/**
 * @brief Allocate enough memory for return and write into allocated string
 * 
 * @param return_string char**, address of the string pointer
 * @param format char*, format string
 * @param ... variable number of arguments
 * @return int negative on error, or the number of characters written 
 * 			(excluding the null byte used to end output to strings)
 */
int		ft_sprintf(char **return_string, const char *format, ...);

/**
 * @brief Write output to the specified file_descriptor
 * 
 * @param file_descriptor int, file descriptor
 * @param format char*, format string
 * @param ap va_args, list of arguments whose number and types are not known
 * @return int negative on error, or the number of characters written 
 * 			(excluding the null byte used to end output to strings)
 */
int		ft_vdprintf(int file_descriptor, const char *format, va_list ap);

/**
 * @brief Allocate enough memory for return and write into allocated string
 * 
 * @param return_string char**, address of the string pointer
 * @param format char*, format string
 * @param ap va_args, list of arguments whose number and types are not known
 * @return int negative on error, or the number of characters written 
 * 			(excluding the null byte used to end output to strings)
 */
int		ft_vsprintf(char **return_string, const char *s, va_list ap);

/* ****************************************************************************
 * HELPER FUNCTIONS
 *************************************************************************** */

/**
 * @brief Allocate memory and set it to zeroes
 * 
 * @param size size of allocated memory area
 * @return void* pointer to the memory
 */
void	*ft_memalloc(size_t size);

/**
 * @brief Allocate a null-terminated string filled with character c
 * 
 * @param c character to fill the string
 * @param size length of string without counting ending null-byte
 * @return char* allocated string or NULL on error
*/
char	*ft_stralloc(char c, size_t size);
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
char	*lltoa_base(int64_t n, int base, t_bool upper_case, int8_t grp_thsnd);

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
char	*ulltoa_base(uint64_t n, int base, t_bool upper_case, int8_t grp_thsnd);

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
char	*dbltostr_base(long double n, int base, t_bool upper, uint64_t prec);

/**
 * @brief Join n heap-allocated strings and free them, NULL is ignored
 * 
 * @param n amount of parameters
 * @param ... char* string pointers
 * @return char* string on success, NULL on error
 */
char	*string_joiner(size_t n, ...);
#endif
