/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 21:07:30 by pcovalio          #+#    #+#             */
/*   Updated: 2022/12/03 12:21:52 by pcovalio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len;

	if (dst && src)
	{
		len = ft_strlen(src);
		if (len < size)
		{
			ft_memcpy(dst, src, len);
			dst[len] = 0;
		}
		else if (size)
		{
			ft_memcpy(dst, src, size);
			dst[size - 1] = 0;
		}
		return (len);
	}
	return (0);
}
