/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 20:39:40 by pcovalio          #+#    #+#             */
/*   Updated: 2022/12/04 08:18:49 by pcovalio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	return ((c > 8 && c < 14) || c == ' ');
}

int	ft_atoi(const char *s)
{
	long	i;
	int		is_neg;

	i = 0;
	if (!s)
		return (i);
	is_neg = 1;
	while (ft_isspace(*s))
		++s;
	if (*s == '-')
		is_neg = -is_neg;
	if (*s == '-' || *s == '+')
		++s;
	while (ft_isdigit(*s))
	{
		i = (i * 10) + (*s - '0');
		++s;
	}
	return ((int)(i * is_neg));
}
