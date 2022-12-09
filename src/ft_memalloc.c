/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 21:10:05 by pcovalio          #+#    #+#             */
/*   Updated: 2022/12/09 21:29:02 by pcovalio         ###   ########.fr       */
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
