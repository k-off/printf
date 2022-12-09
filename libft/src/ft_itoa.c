/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 20:45:03 by pcovalio          #+#    #+#             */
/*   Updated: 2022/12/04 08:19:07 by pcovalio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	tmp[12];
	int		pos;
	int		is_neg;

	if (n == -2147483648)
		return (ft_strdup("-2147483648\0"));
	pos = 11;
	tmp[pos] = 0;
	is_neg = 0;
	if (n < 0)
	{
		is_neg = 1;
		n = -n;
	}
	while (1)
	{
		tmp[--pos] = '0' + n % 10;
		n /= 10;
		if (!n)
			break ;
	}
	if (is_neg)
		tmp[--pos] = '-';
	return (ft_strdup(&tmp[pos]));
}
