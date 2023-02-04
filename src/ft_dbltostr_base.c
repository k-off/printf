/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbltostr_base.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 14:09:41 by pcovalio          #+#    #+#             */
/*   Updated: 2023/02/04 13:02:32 by pcovalio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/**
 * @brief Detect whether 80-bit extended precision number
 * 		is set to one of the special states (-nan, nan, -inf, inf)
 * 
 * @param n long double, number to be converted
 * @param upper t_bool, return an upper-case string if set to true
 * @return char* result string, if number is in a special state or NULL
 */
static char	*infnan(long double n, t_bool upper)
{
	if (*((uint32_t *)(&((char *)(&n))[6])) == 0xFFFFC000)
	{
		if (upper == false)
			return (ft_strdup("-nan"));
		return (ft_strdup("-NAN"));
	}
	if (*((uint32_t *)(&((char *)(&n))[6])) == 0x7FFFC000)
	{
		if (upper == false)
			return (ft_strdup("nan"));
		return (ft_strdup("NAN"));
	}
	if (*((uint32_t *)(&((char *)(&n))[6])) == 0x7FFF8000)
	{
		if (upper == false)
			return (ft_strdup("inf"));
		return (ft_strdup("INF"));
	}
	if (*((uint32_t *)(&((char *)(&n))[6])) == 0xFFFF8000)
	{
		if (upper == false)
			return (ft_strdup("-inf"));
		return (ft_strdup("-INF"));
	}
	return (NULL);
}

/**
 * @brief Convert decimal part of a float into a string with required base
 * 		and case
 * 
 * @param n long double, number to be converted
 * @param base int, required base (ie binary hex etc), bases 2-36 are supported
 * @param upper t_bool, bases 10+ use uppercase letters if set to true
 * @return char* 
 */
static char	*dbl_intpart(long double n, int base, t_bool upper)
{
	size_t	zeros;
	char	*res;

	zeros = 0;
	while (n >= 1 && (uint64_t)n == 0)
	{
		++zeros;
		n /= base;
	}
	res = string_joiner(2, ulltoa_base((uint64_t)n, base, upper, 0), \
						ft_stralloc('0', zeros));
	return (res);
}

/**
 * @brief Convert decimal part of a float into a string with required base,
 * 		case and precision
 * 
 * @param n long double, number to be converted
 * @param base int, required base (ie binary hex etc), bases 2-36 are supported
 * @param upper t_bool, bases 10+ use uppercase letters if set to true
 * @param prec uint64_t, required precision
 * @return char* 
 */
static char	*dbl_decpart(long double n, int base, t_bool upper, uint64_t prec)
{
	char		*r;
	uint64_t	zeros_before;
	uint8_t		lim;

	zeros_before = 0;
	n -= (uint64_t)n;
	while ((int)(n * base) == 0 && prec--)
	{
		n *= base;
		++zeros_before;
	}
	if ((int)(n) == 0 && (long)prec < 1 && zeros_before > 0)
		--zeros_before;
	r = NULL;
	lim = 19;
	while (prec && lim)
		n *= (base * (prec-- >= 1 && lim-- > 1));
	r = string_joiner(2, r, ulltoa_base((uint64_t)n, base, upper, prec));
	return (string_joiner(3, ft_stralloc('0', zeros_before), r, \
							ft_stralloc('0', prec)));
}

/**
 * @brief Round the least significant digit that has to be printed if needed.
 * 		Only up to 19 decimal digits are handled.
 * 
 * @param n number to be printed
 * @param prec reqired precision
 */
static void	ft_round(long double *n, uint64_t prec)
{
	long double	tmp;
	long double	cor;

	tmp = 5.0L;
	cor = 1.0L / (1ULL << 62);
	tmp /= 10.0L;
	while (prec--)
	{
		tmp /= 10.0L;
		if (cor < 0.1L)
			cor *= 10.0L;
	}
	tmp *= (1.0L + cor);
	*n += tmp;
}

char	*dbltostr_base(long double n, int base, t_bool upper, uint64_t prec)
{
	char	*res;

	if (base < 2 || base > 36)
		return (NULL);
	res = infnan(n, upper);
	if (res != NULL)
		return (res);
	if (n < 0 || (n == 0 && (*((uint8_t *)(&((char *)(&n))[9])) >> 7) == 1))
	{
		*((uint8_t *)(&((char *)(&n))[9])) ^= (1 << 7);
		res = string_joiner(2, res, ft_strdup("-"));
	}
	ft_round(&n, prec);
	res = string_joiner(2, res, dbl_intpart(n, base, upper));
	if (prec > 0 && res != NULL)
		res = string_joiner(3, res, ft_strdup("."), \
							dbl_decpart(n, base, upper, prec));
	return (res);
}
