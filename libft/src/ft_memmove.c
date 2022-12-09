/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 20:56:50 by pcovalio          #+#    #+#             */
/*   Updated: 2022/12/03 11:21:04 by pcovalio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	tmp;

	if (dest < src)
	{
		tmp = 0;
		while (tmp < n)
		{
			((char *)dest)[tmp] = ((char *)src)[tmp];
			++tmp;
		}
	}
	else if (dest > src)
		while (n--)
			((char *)dest)[n] = ((char *)src)[n];
	return (dest);
}
