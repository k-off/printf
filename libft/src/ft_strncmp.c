/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 21:10:08 by pcovalio          #+#    #+#             */
/*   Updated: 2022/12/03 13:39:41 by pcovalio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (s1 && s2)
	{
		if (!n)
			return (0);
		i = -1;
		while (++i < n)
			if (!s1[i] || !s2[i] || s1[i] != s2[i])
				break ;
		i -= (i == n);
		return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
	}
	return (0);
}
