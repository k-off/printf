/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 21:11:55 by pcovalio          #+#    #+#             */
/*   Updated: 2022/12/03 18:56:38 by pcovalio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	right;
	size_t	left;
	char	*ret;

	if (s1 && set)
	{
		right = ft_strlen(s1);
		left = 0;
		while (left < right && ft_strchr(set, s1[left]))
			++left;
		if (left < right && right)
			--right;
		while (left < right && ft_strchr(set, s1[right]))
			--right;
		ret = (char *)malloc(right - left + 2);
		if (!ret)
			return (0);
		if (!ft_strlcpy(ret, &s1[left], right - left + 2))
			ret[0] = 0;
		return (ret);
	}
	return (0);
}
