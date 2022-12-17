/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 21:10:05 by pcovalio          #+#    #+#             */
/*   Updated: 2022/12/17 10:28:18 by pcovalio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	*ft_memalloc(size_t size)
{
	char	*ret;
	size_t	i;

	ret = (char *)malloc(size);
	if (!ret)
	{
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		ret[i++] = 0;
	}
	return ((void *)ret);
}

char	*ft_stralloc(char c, size_t size)
{
	char	*ret;
	size_t	i;

	ret = (char *)malloc(size + 1);
	if (!ret)
	{
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		ret[i++] = c;
	}
	ret[size] = 0;
	return ((void *)ret);
}
