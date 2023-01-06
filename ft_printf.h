/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:10:31 by pcovalio          #+#    #+#             */
/*   Updated: 2023/01/04 15:14:37 by pcovalio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <limits.h>

/**
 * @brief Write output to stdout, the standard output stream
 * 
 * @param format char*, format string
 * @param ... variable number of arguments
 * @return int negative on error, or the number of characters written
 * 			(excluding the null byte used to end output to strings)
 */
int			ft_printf(const char *format, ...);

/**
 * @brief Write output to the specified file_descriptor
 * 
 * @param file_descriptor int, file descriptor
 * @param format char*, format string
 * @param ... variable number of arguments
 * @return int negative on error, or the number of characters written
 * 			(excluding the null byte used to end output to strings)
 */
int			ft_dprintf(int file_descriptor, const char *format, ...);

/**
 * @brief Allocate enough memory for return and write into allocated string
 * 
 * @param return_string char**, address of the string pointer
 * @param format char*, format string
 * @param ... variable number of arguments
 * @return int negative on error, or the number of characters written 
 * 			(excluding the null byte used to end output to strings)
 */
int			ft_sprintf(char **return_string, const char *format, ...);

/**
 * @brief Write output to the specified file_descriptor
 * 
 * @param file_descriptor int, file descriptor
 * @param format char*, format string
 * @param ap va_args, list of arguments whose number and types are not known
 * @return int negative on error, or the number of characters written 
 * 			(excluding the null byte used to end output to strings)
 */
int			ft_vdprintf(int file_descriptor, const char *format, va_list ap);

/**
 * @brief Allocate enough memory for return and write into allocated string
 * 
 * @param return_string char**, address of the string pointer
 * @param format char*, format string
 * @param ap va_args, list of arguments whose number and types are not known
 * @return int negative on error, or the number of characters written 
 * 			(excluding the null byte used to end output to strings)
 */
int			ft_vsprintf(char **return_string, const char *s, va_list ap);

#endif
