/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 21:10:23 by pcovalio          #+#    #+#             */
/*   Updated: 2022/12/03 13:26:11 by pcovalio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (s1 && s2)
	{
		if (!*s2)
			return ((char *)s1);
		if (ft_strlen(s2) > n || ft_strlen(s2) > ft_strlen(s1))
			return (0);
		while (i < n && i <= (ft_strlen(s1) - ft_strlen(s2)))
		{
			j = 0;
			while (s1[i + j] == s2[j] && i + j < n)
			{
				++j;
				if (!s2[j])
					return (&((char *)s1)[i]);
				if (!s1[i + j])
					return (0);
			}
			++i;
		}
	}
	return (0);
}

/*
#include <stdio.h>
int main()
{
	char *s = ft_strnstr("lorem ipsum dolor sit amet", "ipsumm", 30);
	if (s)
		printf("%s\n", s);
	else
		printf("NULL\n");
}
*/
