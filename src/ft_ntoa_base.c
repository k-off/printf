/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ntoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 21:28:48 by pcovalio          #+#    #+#             */
/*   Updated: 2022/12/09 22:16:34 by pcovalio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*ulltoa_base(uint64_t n, int base, t_bool upper_case, int8_t grp_thsnd)
{
	char	*set[2];
	char	res[65];
	size_t	pos;

	if (base < 2 || base > 36)
		return (NULL);
	set[0] = "0123456789abcdefghijklmnopqrstuvwxyz";
	set[1] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	res[64] = 0;
	pos = 64;
	while (1)
	{
		if (base == 10 && pos < 63 && (65 - pos) % 4 == 0 && grp_thsnd)
			res[--pos] = grp_thsnd;
		res[--pos] = set[upper_case][n % base];
		n /= base;
		if (!n)
			break ;
	}
	return (ft_strdup(&res[pos]));
}

char	*lltoa_base(int64_t n, int base, t_bool upper_case, int8_t grp_thsnd)
{
	if (base < 2 || base > 36)
		return (NULL);
	if (n >= 0)
		return (ulltoa_base(n, base, upper_case, grp_thsnd));
	else
		return (string_joiner(2, ft_strdup("-"), \
			ulltoa_base(-n, base, upper_case, grp_thsnd)));
}


char	*dbltoa_base(long double n, int base, t_bool upper_case, int64_t prec)
{
	// long double tmp;
	// uint64_t	int_side[5];
	(void)n;
	(void)base;
	(void)upper_case;
	(void)prec;

	return (NULL);
}