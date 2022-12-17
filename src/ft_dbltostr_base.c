/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbltostr_base.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 14:09:41 by pcovalio          #+#    #+#             */
/*   Updated: 2022/12/17 19:13:36 by pcovalio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdio.h>
#include <unistd.h>

static char *infnan(long double n, t_bool upper)
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
	return NULL;
}

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

static char	*dbl_decpart(long double n, int base, t_bool upper, uint64_t prec)
{
	char		*r;
	uint64_t	zeros_before;
	uint8_t		lim;

	zeros_before = 0;
	n -= (uint64_t)n;
	while ((int)(n * 10) == 0 && prec--)
	{
		n *= 10;
		++zeros_before;
	}
	r = NULL;
	if (n != 0 && prec > 0)
	{
		lim = 19;
		while (prec-- && lim--)
			n *= 10;
		r = string_joiner(2, r, ulltoa_base((uint64_t)n, base, upper, prec));
		printf("\n%Lf: %s\n", n, r);
	}
	return (string_joiner(3, ft_stralloc('0', zeros_before), r, \
							ft_stralloc('0', prec)));
}

static void	ft_round(long double *n, uint64_t prec)
{
	long double	tmp;
	long double cor;

	tmp = 10.0L;
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
	char *res;

	if (base < 2 || base > 36)
		return (NULL);
	if (prec < 0)
		return (NULL);
	write(1, "0", 1);
	res = infnan(n, upper);
	write(1, "0", 1);
	if (res != NULL)
		return (res);
	else
		write(1, "0", 1);
	if (n < 0 || (n == 0 && (*((uint8_t *)(&((char *)(&n))[9])) >> 7) == 1))
	{
		*((uint8_t *)(&((char *)(&n))[9])) ^= (1 << 7);
		res = string_joiner(2, res, ft_strdup("-"));
	}
	write(1, "0", 1);
	ft_round(&n, prec);
	write(1, "1", 1);
	res = string_joiner(2, res, dbl_intpart(n, base, upper));
	printf("%s\n", res);
write(1, "2", 1);
	if (prec > 0 && res != NULL)
		res = string_joiner(3, res, ft_strdup("."), \
							dbl_decpart(n, base, upper, prec));
	return (res);
}
