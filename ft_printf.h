/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:10:31 by pcovalio          #+#    #+#             */
/*   Updated: 2023/02/05 08:42:05 by pcovalio         ###   ########.fr       */
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
 * @brief Write a formatted string to standard output
 * 
 * @param format char*, format string
 * @param ... variable number of arguments
 * @return int negative on error, or the number of characters written
 * 			(excluding the null byte used to end output to strings)
 */
int			ft_printf(const char *format, ...);

/**
 * @brief Write a formatted string to a specified filedescriptor
 * 
 * @param file_descriptor int, file descriptor
 * @param format char*, format string
 * @param ... variable number of arguments
 * @return int negative on error, or the number of bytes written
 * 			(excluding the null byte used to end output to strings)
 */
int			ft_dprintf(int file_descriptor, const char *format, ...);

/**
 * @brief Allocate and store formatted string into provided memory address
 * 
 * @param return_string char**, pointer to the address of newly allocated string
 * @param format char*, format string
 * @param ... variable number of arguments
 * @return int negative on error, or the number of bytes allocated
 */
int			ft_sprintf(char **return_string, const char *format, ...);

/**
 * @brief Write formatted string to a specified filedescriptor
 * 
 * @param file_descriptor int, file descriptor
 * @param format char*, format string
 * @param ap va_args, list of arguments whose number and types are not known
 * @return int negative on error, or the number of bytes written 
 * 			(excluding the null byte used to end output to strings)
 */
int			ft_vdprintf(int file_descriptor, const char *format, va_list ap);

/**
 * @brief Allocate and store formatted string into provided memory address
 * 
 * @param return_string char**, pointer to the address of newly allocated string
 * @param format char*, format string
 * @param ap va_args, initialized var args list that has to be closed by caller
 * @return int negative on error, or the number of bytes allocated
 */
int			ft_vsprintf(char **return_string, const char *s, va_list ap);

#endif
