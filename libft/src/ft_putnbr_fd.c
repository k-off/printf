/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 21:01:30 by pcovalio          #+#    #+#             */
/*   Updated: 2022/12/04 08:19:42 by pcovalio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

static char	*ft_setlong(char *s, int is_neg, int is_pos, long long n)
{
	if (n < 0)
	{
		is_neg = 1;
		n = -n;
	}
	while (n)
	{
		*s = '0' + n % 10;
		n /= 10;
		--s;
	}
	if (is_neg)
		*s = '-';
	else if (is_pos)
		++s;
	return (s);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	s[21];

	s[20] = 0;
	s[19] = '0';
	ft_putstr_fd(ft_setlong(&s[19], n < 0, n > 0, n), fd);
}
