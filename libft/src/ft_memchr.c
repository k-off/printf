/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 20:54:57 by pcovalio          #+#    #+#             */
/*   Updated: 2022/12/03 16:30:41 by pcovalio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = -1;
	if (s)
		while (++i < n)
			if (((unsigned char *)s)[i] == (unsigned char)c)
				return (&((unsigned char *)s)[i]);
	return (0);
}
